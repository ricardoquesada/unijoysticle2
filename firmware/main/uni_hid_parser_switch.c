/****************************************************************************
http://retro.moe/unijoysticle2

Copyright 2019 Ricardo Quesada

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
****************************************************************************/

#include "uni_hid_parser_switch.h"

#include "hid_usage.h"
#include "uni_debug.h"
#include "uni_gamepad.h"
#include "uni_hid_device.h"
#include "uni_hid_parser.h"

// Support for Nintendo Switch Pro gamepad.

static const uint16_t SWITCH_VID = 0x057e;
static const uint16_t SWITCH_PID = 0x2009;
static const uint8_t SWITCH_HID_DESCRIPTOR[] = {
    0x05, 0x01, 0x09, 0x05, 0xA1, 0x01, 0x06, 0x01, 0xFF, 0x85, 0x21, 0x09,
    0x21, 0x75, 0x08, 0x95, 0x30, 0x81, 0x02, 0x85, 0x30, 0x09, 0x30, 0x75,
    0x08, 0x95, 0x30, 0x81, 0x02, 0x85, 0x31, 0x09, 0x31, 0x75, 0x08, 0x96,
    0x69, 0x01, 0x81, 0x02, 0x85, 0x32, 0x09, 0x32, 0x75, 0x08, 0x96, 0x69,
    0x01, 0x81, 0x02, 0x85, 0x33, 0x09, 0x33, 0x75, 0x08, 0x96, 0x69, 0x01,
    0x81, 0x02, 0x85, 0x3F, 0x05, 0x09, 0x19, 0x01, 0x29, 0x10, 0x15, 0x00,
    0x25, 0x01, 0x75, 0x01, 0x95, 0x10, 0x81, 0x02, 0x05, 0x01, 0x09, 0x39,
    0x15, 0x00, 0x25, 0x07, 0x75, 0x04, 0x95, 0x01, 0x81, 0x42, 0x05, 0x09,
    0x75, 0x04, 0x95, 0x01, 0x81, 0x01, 0x05, 0x01, 0x09, 0x30, 0x09, 0x31,
    0x09, 0x33, 0x09, 0x34, 0x16, 0x00, 0x00, 0x27, 0xFF, 0xFF, 0x00, 0x00,
    0x75, 0x10, 0x95, 0x04, 0x81, 0x02, 0x06, 0x01, 0xFF, 0x85, 0x01, 0x09,
    0x01, 0x75, 0x08, 0x95, 0x30, 0x91, 0x02, 0x85, 0x10, 0x09, 0x10, 0x75,
    0x08, 0x95, 0x30, 0x91, 0x02, 0x85, 0x11, 0x09, 0x11, 0x75, 0x08, 0x95,
    0x30, 0x91, 0x02, 0x85, 0x12, 0x09, 0x12, 0x75, 0x08, 0x95, 0x30, 0x91,
    0x02, 0xC0,
};

enum switch_flags {
  SWITCH_MODE_NONE = 0,    // Mode not set yet
  SWITCH_MODE_NORMAL = 1,  // Gamepad using regular buttons
  SWITCH_MODE_ACCEL = 2,   // Gamepad using gyro+accel
};

// Taken from Linux kernel: hid-nintendo.c
enum switchproto_reqs {
  /* Input Reports */
  SWITCH_INPUT_SUBCMD_REPLY = 0x21,
  SWITCH_INPUT_IMU_DATA = 0x30,
  SWITCH_INPUT_MCU_DATA = 0x31,
  SWITCH_INPUT_BUTTON_EVENT = 0x3F,
};

// Nintendo Switch output-report info taken from:
// https://github.com/DanielOgorchock/linux/blob/ogorchock/drivers/hid/hid-nintendo.c
enum switch_subcmd {
  SUBCMD_SET_REPORT_MODE = 0x03,
  SUBCMD_SET_LEDS = 0x30,
  SUBCMD_ENABLE_IMU = 0x40,
};

struct switch_subcmd_request {
  // Report related
  uint8_t transaction_type;  // type of transaction
  uint8_t report_id;  // must be 0x01 for subcommand, 0x10 for rumble only

  // Data related
  uint8_t packet_num;  // increment by 1 for each packet sent. It loops in 0x0 -
                       // 0xF range.
  // Rumble not supported at the moment. For further info see:
  // https://github.com/dekuNukem/Nintendo_Switch_Reverse_Engineering/blob/master/rumble_data_table.md
  uint8_t rumble_left[4];
  uint8_t rumble_right[4];
  uint8_t subcmd_id;
  uint8_t data[0];  // length depends on the subcommand
} __attribute__((__packed__));

// switch_instance_t represents data used by the Switch driver instance.
typedef struct switch_instance_s {
  uint8_t version;
  uint8_t mode;
} switch_instance_t;

struct switch_report_3f_s {
  uint8_t button_main;
  uint8_t button_aux;
  uint8_t hat;
  uint8_t x_lsb;
  uint8_t x_msb;
  uint8_t y_lsb;
  uint8_t y_msb;
  uint8_t rx_lsb;
  uint8_t rx_msb;
  uint8_t ry_lsb;
  uint8_t ry_msb;
} __attribute__((packed));

static void process_input_subcmd_reply(struct uni_hid_device_s* d,
                                       const uint8_t* report, int len);
static void process_input_imu_data(struct uni_hid_device_s* d,
                                   const uint8_t* report, int len);
static void process_input_button_event(struct uni_hid_device_s* d,
                                       const uint8_t* report, int len);
static switch_instance_t* get_switch_instance(uni_hid_device_t* d);
static void send_subcmd(uni_hid_device_t* d, struct switch_subcmd_request* r,
                        int len);

void uni_hid_parser_switch_init_report(uni_hid_device_t* d) {
  // Reset old state. Each report contains a full-state.
  d->gamepad.updated_states = 0;
  d->gamepad.dpad = 0;
  d->gamepad.buttons = 0;
  d->gamepad.misc_buttons = 0;
}

void uni_hid_parser_switch_parse_raw(struct uni_hid_device_s* d,
                                     const uint8_t* report, uint16_t len) {
  if (len < 12) {
    loge("Nintendo Switch: Invalid packet len; got %d, want >= 12\n", len);
    return;
  }
  switch (report[0]) {
    case SWITCH_INPUT_SUBCMD_REPLY:
      process_input_subcmd_reply(d, report, len);
      break;
    case SWITCH_INPUT_IMU_DATA:
      process_input_imu_data(d, report, len);
      break;
    case SWITCH_INPUT_BUTTON_EVENT:
      process_input_button_event(d, report, len);
      break;
    default:
      loge("Nintendo Switch: unsupported report id: 0x%02x\n", report[0]);
      printf_hexdump(report, len);
  }
}

// Process 0x3f input report: SWITCH_INPUT_BUTTON_EVENT
static void process_input_button_event(struct uni_hid_device_s* d,
                                       const uint8_t* report, int len) {
  // Expecting something like:
  // (a1) 3F 00 00 08 D0 81 0F 88 F0 81 6F 8E
  UNUSED(len);
  uni_gamepad_t* gp = &d->gamepad;
  const struct switch_report_3f_s* r =
      (const struct switch_report_3f_s*)&report[1];

  // Button main
  gp->buttons |= (r->button_main & 0b00000001) ? BUTTON_A : 0;           // B
  gp->buttons |= (r->button_main & 0b00000010) ? BUTTON_B : 0;           // A
  gp->buttons |= (r->button_main & 0b00000100) ? BUTTON_X : 0;           // Y
  gp->buttons |= (r->button_main & 0b00001000) ? BUTTON_Y : 0;           // X
  gp->buttons |= (r->button_main & 0b00010000) ? BUTTON_SHOULDER_L : 0;  // L
  gp->buttons |= (r->button_main & 0b00100000) ? BUTTON_SHOULDER_R : 0;  // R
  gp->buttons |= (r->button_main & 0b01000000) ? BUTTON_TRIGGER_L : 0;   // ZL
  gp->buttons |= (r->button_main & 0b10000000) ? BUTTON_TRIGGER_R : 0;   // ZR
  gp->updated_states |=
      GAMEPAD_STATE_BUTTON_A | GAMEPAD_STATE_BUTTON_B | GAMEPAD_STATE_BUTTON_X |
      GAMEPAD_STATE_BUTTON_Y | GAMEPAD_STATE_BUTTON_SHOULDER_L |
      GAMEPAD_STATE_BUTTON_SHOULDER_R | GAMEPAD_STATE_BUTTON_TRIGGER_L |
      GAMEPAD_STATE_BUTTON_TRIGGER_R;

  // Button aux
  gp->misc_buttons |= (r->button_aux & 0b00000001) ? MISC_BUTTON_BACK : 0;  // -
  gp->buttons |= (r->button_aux & 0b00000010) ? 0 : 0;  // + (unmapped)
  gp->buttons |= (r->button_aux & 0b00000100) ? BUTTON_THUMB_L : 0;  // Thumb L
  gp->buttons |= (r->button_aux & 0b00001000) ? BUTTON_THUMB_R : 0;  // Thumb R
  gp->misc_buttons |=
      (r->button_aux & 0b00010000) ? MISC_BUTTON_SYSTEM : 0;  // Home
  gp->misc_buttons |=
      (r->button_aux & 0b00100000) ? MISC_BUTTON_HOME : 0;  // Circle
  gp->updated_states |= GAMEPAD_STATE_MISC_BUTTON_HOME |
                        GAMEPAD_STATE_MISC_BUTTON_SYSTEM |
                        GAMEPAD_STATE_MISC_BUTTON_BACK;
  gp->updated_states |=
      GAMEPAD_STATE_BUTTON_THUMB_L | GAMEPAD_STATE_BUTTON_THUMB_R;

  // Dpad
  gp->dpad = uni_hid_parser_hat_to_dpad(r->hat);
  gp->updated_states |= GAMEPAD_STATE_DPAD;

  // Axis
  gp->axis_x = ((r->x_msb << 8) | r->x_lsb) * AXIS_NORMALIZE_RANGE / 65536 -
               AXIS_NORMALIZE_RANGE / 2;
  gp->axis_y = ((r->y_msb << 8) | r->y_lsb) * AXIS_NORMALIZE_RANGE / 65536 -
               AXIS_NORMALIZE_RANGE / 2;
  gp->axis_rx = ((r->rx_msb << 8) | r->rx_lsb) * AXIS_NORMALIZE_RANGE / 65536 -
                AXIS_NORMALIZE_RANGE / 2;
  gp->axis_ry = ((r->ry_msb << 8) | r->ry_lsb) * AXIS_NORMALIZE_RANGE / 65536 -
                AXIS_NORMALIZE_RANGE / 2;
  gp->updated_states |= GAMEPAD_STATE_AXIS_X | GAMEPAD_STATE_AXIS_Y |
                        GAMEPAD_STATE_AXIS_RX | GAMEPAD_STATE_AXIS_RY;
}

// Process 0x21 input report: SWITCH_INPUT_SUBCMD_REPLY
static void process_input_subcmd_reply(struct uni_hid_device_s* d,
                                       const uint8_t* report, int len) {
  UNUSED(len);
  // Report has this format:
  // 21 D9 80 08 10 00 18 A8 78 F2 C7 70 0C 80 30 00 00 00 00 00 00 00 00 00 00
  // 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  printf_hexdump(report, len);
  switch_instance_t* ins = get_switch_instance(d);
  if (ins->mode == SWITCH_MODE_NONE) {
    // Mode not set yet, set it. 4th byte contains the "main" buttons.
    // Override it if "A" button is pressed.
    if (report[3] & 0x08) {
      logi("Switch: setting Accelerometer mode\n");
      ins->mode = SWITCH_MODE_ACCEL;
      // Update LED when Accel mode is enabled.
      uint8_t out[sizeof(struct switch_subcmd_request) + 1] = {0};

      struct switch_subcmd_request* req =
          (struct switch_subcmd_request*)&out[0];
      req->transaction_type = 0xa2;  // DATA | TYPE_OUTPUT
      req->report_id = 0x01;         // 0x01 for sub commands
      // req->subcmd_id = SUBCMD_SET_LEDS;
      req->subcmd_id = SUBCMD_SET_REPORT_MODE;
      // req->data[0] = d->joystick_port | 0x04;
      req->data[0] = 0x30; /* type of report: standard, full */
      send_subcmd(d, req, sizeof(out));

      // Enable IMU
      req->subcmd_id = SUBCMD_ENABLE_IMU;
      req->data[0] = 1; /* enable */
      send_subcmd(d, req, sizeof(out));
    } else {
      logi("Switch: setting Normal mode\n");
      ins->mode = SWITCH_MODE_NORMAL;
    }
  }
}

// Process 0x30 input report: SWITCH_INPUT_IMU_DATA
static void process_input_imu_data(struct uni_hid_device_s* d,
                                   const uint8_t* report, int len) {
  UNUSED(d);
  // Expecting something like:
  // (a1) 31 ...
  printf_hexdump(report, len);
}

void uni_hid_parser_switch_update_led(uni_hid_device_t* d) {
  // 1 == SET_LEDS subcmd len
  uint8_t report[sizeof(struct switch_subcmd_request) + 1] = {0};

  struct switch_subcmd_request* req = (struct switch_subcmd_request*)&report[0];
  req->transaction_type = 0xa2;  // DATA | TYPE_OUTPUT
  req->report_id = 0x01;         // 0x01 for sub commands
  req->subcmd_id = SUBCMD_SET_LEDS;
  req->data[0] = d->joystick_port;
  send_subcmd(d, req, sizeof(report));
}

uint8_t uni_hid_parser_switch_does_packet_match(struct uni_hid_device_s* d,
                                                const uint8_t* packet,
                                                int len) {
  // A switch packet looks like this:
  // A1 3F 00 00 08 00 80 00 80 00 80 00 80
  if (len != 13 || packet[0] != 0xa1 || packet[1] != 0x3f) {
    return 0;
  }
  // TODO: don't set the HID descriptor. It is faster to parse the raw
  // packet. It seems that Nintendo Switch has a stable packet format.
  uni_hid_device_set_hid_descriptor(d, SWITCH_HID_DESCRIPTOR,
                                    sizeof(SWITCH_HID_DESCRIPTOR));
  uni_hid_device_set_vendor_id(d, SWITCH_VID);
  uni_hid_device_set_product_id(d, SWITCH_PID);
  uni_hid_device_guess_controller_type_from_pid_vid(d);
  uni_hid_device_set_sdp_device(NULL);
  uni_hid_device_set_state(d, STATE_SDP_VENDOR_FETCHED);
  logi(
      "Switch: Device detected as Nintendo Switch Pro controller using "
      "heuristics\n");
  return 1;
}

//
// Helpers
//
static switch_instance_t* get_switch_instance(uni_hid_device_t* d) {
  return (switch_instance_t*)&d->data[0];
}

static void send_subcmd(uni_hid_device_t* d, struct switch_subcmd_request* r,
                        int len) {
  static uint8_t packet_num = 0;
  r->packet_num = packet_num++;
  if (packet_num > 0x0f) packet_num = 0;
  uni_hid_device_queue_report(d, (const uint8_t*)r, len);
}
