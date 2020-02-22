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
// Stick calibration start address. Taken from:
// https://github.com/dekuNukem/Nintendo_Switch_Reverse_Engineering/blob/master/spi_flash_notes.md
// TODO: should we use 0x8000 instead?
static const uint16_t SWITCH_CAL_DATA_ADDR = 0x603d;
// 12 bits per value * 2 axis (x,y) * 3 values (min,center,max) * 2 sticks
// 12 * 2 * 3 * 2 == 144 bits (18 bytes)
static const uint16_t SWITCH_CAL_DATA_SIZE = 18;

enum switch_state {
  STATE_UNINIT,
  STATE_SETUP,
  STATE_REQ_DEV_INFO,            // What controller
  STATE_READ_STICK_CALIBRATION,  // Calibration info
  STATE_SET_FULL_REPORT,         // Request report 0x30
  STATE_ENABLE_IMU,              // Enable/Disable gyro/accel
  STATE_READY,                   // Gamepad setup ready!
};

enum switch_flags {
  SWITCH_MODE_NONE,    // Mode not set yet
  SWITCH_MODE_NORMAL,  // Gamepad using regular buttons
  SWITCH_MODE_ACCEL,   // Gamepad using gyro+accel
};

// Taken from Linux kernel: hid-nintendo.c
enum switch_proto_reqs {
  /* Input Reports */
  SWITCH_INPUT_SUBCMD_REPLY = 0x21,
  SWITCH_INPUT_IMU_DATA = 0x30,
  SWITCH_INPUT_MCU_DATA = 0x31,
  SWITCH_INPUT_BUTTON_EVENT = 0x3F,
};

// Received in SUBCMD_REQ_DEV_INFO
enum switch_controller_types {
  SWITCH_CONTROLLER_TYPE_JCL = 0x01,  // Joy-con left
  SWITCH_CONTROLLER_TYPE_JCR = 0x02,  // Joy-con right
  SWITCH_CONTROLLER_TYPE_PRO = 0x03,  // Gamepad Pro
};

// Nintendo Switch output-report info taken from:
// https://github.com/DanielOgorchock/linux/blob/ogorchock/drivers/hid/hid-nintendo.c
enum switch_subcmd {
  SUBCMD_REQ_DEV_INFO = 0x02,
  SUBCMD_SET_REPORT_MODE = 0x03,
  SUBCMD_SPI_FLASH_READ = 0x10,
  SUBCMD_SET_LEDS = 0x30,
  SUBCMD_ENABLE_IMU = 0x40,
};

typedef struct switch_cal_stick_s {
  int16_t min;
  int16_t center;
  int16_t max;
} switch_cal_stick_t;

// switch_instance_t represents data used by the Switch driver instance.
typedef struct switch_instance_s {
  uint8_t state;
  uint8_t mode;
  uint8_t firmware_hi;
  uint8_t firmware_lo;
  uint8_t controller_type;
  // Factory calibration info
  switch_cal_stick_t cal_x;
  switch_cal_stick_t cal_y;
  switch_cal_stick_t cal_rx;
  switch_cal_stick_t cal_ry;
} switch_instance_t;

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

struct switch_report_3f_s {
  uint8_t buttons_main;
  uint8_t buttons_aux;
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

struct switch_report_30_s {
  uint8_t buttons_right;
  uint8_t buttons_misc;
  uint8_t buttons_left;
  uint8_t stick_left[3];
  uint8_t stick_right[3];
  uint8_t vibrator_report;
  uint8_t imu[0];
} __attribute__((packed));

struct switch_report_21_s {
  uint8_t report_id;
  uint8_t timer;
  uint8_t bat_con;
  struct switch_report_30_s status;
  uint8_t ack;
  uint8_t subcmd_id;
  uint8_t data[0];
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
static void process_fsm(struct uni_hid_device_s* d);
static void fsm_request_device_info(struct uni_hid_device_s* d);
static void fsm_read_stick_calibration(struct uni_hid_device_s* d);
static void fsm_set_full_report(struct uni_hid_device_s* d);
static void fsm_enable_imu(struct uni_hid_device_s* d);
static void fsm_update_led(struct uni_hid_device_s* d);
static void process_reply_req_dev_info(struct uni_hid_device_s* d,
                                       const struct switch_report_21_s* r,
                                       int len);
static void process_reply_set_report_mode(struct uni_hid_device_s* d,
                                          const struct switch_report_21_s* r,
                                          int len);
static void process_reply_spi_flash_read(struct uni_hid_device_s* d,
                                         const struct switch_report_21_s* r,
                                         int len);
static void process_reply_set_leds(struct uni_hid_device_s* d,
                                   const struct switch_report_21_s* r, int len);
static void process_reply_enable_imu(struct uni_hid_device_s* d,
                                     const struct switch_report_21_s* r,
                                     int len);
static int32_t calibrate_axis(int16_t v, switch_cal_stick_t cal);

void uni_hid_parser_switch_setup(struct uni_hid_device_s* d) {
  switch_instance_t* ins = get_switch_instance(d);

  ins->state = STATE_SETUP;
  ins->mode = SWITCH_MODE_NONE;
  process_fsm(d);
}

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

static void process_fsm(struct uni_hid_device_s* d) {
  switch_instance_t* ins = get_switch_instance(d);
  switch (ins->state) {
    case STATE_SETUP:
      fsm_request_device_info(d);
      break;
    case STATE_REQ_DEV_INFO:
      fsm_read_stick_calibration(d);
      break;
    case STATE_READ_STICK_CALIBRATION:
      fsm_set_full_report(d);
      break;
    case STATE_SET_FULL_REPORT:
      fsm_enable_imu(d);
      break;
    case STATE_ENABLE_IMU:
      fsm_update_led(d);
      break;
    case STATE_READY:
      logi("Switch: gamepad is ready!\n");
      break;
    default:
      loge("Switch: unexpected state: 0x%02x\n", ins->mode);
  }
}

// Reply to SUBCMD_REQ_DEV_INFO
static void process_reply_req_dev_info(struct uni_hid_device_s* d,
                                       const struct switch_report_21_s* r,
                                       int len) {
  UNUSED(len);
  switch_instance_t* ins = get_switch_instance(d);
  if (ins->state > STATE_SETUP && ins->mode == SWITCH_MODE_NONE) {
    // Button "A" must be pressed in orther to enable IMU.
    uint8_t enable_imu = !!(r->status.buttons_right & 0x08);
    if (enable_imu) {
      ins->mode = SWITCH_MODE_ACCEL;
    } else {
      ins->mode = SWITCH_MODE_NORMAL;
    }
  }
  ins->firmware_hi = r->data[0];
  ins->firmware_lo = r->data[1];
  ins->controller_type = r->data[2];
  logi("Switch: Firmware version: %d.%d. Controller type=%d\n", r->data[0],
       r->data[1], r->data[2]);
}

// Reply to SUBCMD_SET_REPORT_MODE
static void process_reply_set_report_mode(struct uni_hid_device_s* d,
                                          const struct switch_report_21_s* r,
                                          int len) {
  UNUSED(d);
  UNUSED(r);
  UNUSED(len);
}

// Reply to SUBCMD_SPI_FLASH_READ
static void process_reply_spi_flash_read(struct uni_hid_device_s* d,
                                         const struct switch_report_21_s* r,
                                         int len) {
  UNUSED(len);
  switch_instance_t* ins = get_switch_instance(d);
  // Assuming this is a stick calibration response
  // TODO: verify address is correct
  if (r->data[4] != SWITCH_CAL_DATA_SIZE) {
    loge("Switch: unexpected spi_read size reply; got %d, want %d\n",
         r->data[4], SWITCH_CAL_DATA_SIZE);
    return;
  }
  // Left stick
  int16_t cal_x_max = r->data[5] | ((r->data[6] & 0x0f) << 8);
  int16_t cal_y_max = (r->data[6] >> 4) | (r->data[7] << 4);
  ins->cal_x.center = r->data[8] | ((r->data[9] & 0x0f) << 8);
  ins->cal_y.center = (r->data[9] >> 4) | (r->data[10] << 4);
  int16_t cal_x_min = r->data[11] | ((r->data[12] & 0x0f) << 8);
  int16_t cal_y_min = (r->data[12] >> 4) | (r->data[13] << 4);
  ins->cal_x.min = ins->cal_x.center - cal_x_min;
  ins->cal_x.max = ins->cal_x.center + cal_x_max;
  ins->cal_y.min = ins->cal_y.center - cal_y_min;
  ins->cal_y.max = ins->cal_y.center + cal_y_max;

  // Right stick
  int16_t cal_rx_max = r->data[14] | ((r->data[15] & 0x0f) << 8);
  int16_t cal_ry_max = (r->data[15] >> 4) | (r->data[16] << 4);
  ins->cal_rx.center = r->data[17] | ((r->data[18] & 0x0f) << 8);
  ins->cal_ry.center = (r->data[18] >> 4) | (r->data[19] << 4);
  int16_t cal_rx_min = r->data[20] | ((r->data[21] & 0x0f) << 8);
  int16_t cal_ry_min = (r->data[21] >> 4) | (r->data[22] << 4);
  ins->cal_rx.min = ins->cal_rx.center - cal_rx_min;
  ins->cal_rx.max = ins->cal_rx.center + cal_rx_max;
  ins->cal_ry.min = ins->cal_ry.center - cal_ry_min;
  ins->cal_ry.max = ins->cal_ry.center + cal_ry_max;

  // It seems that most some clones have a hardcoded calibration value, making
  // it break the standard algorithm.
  if (ins->firmware_hi == 3 && ins->firmware_lo == 72 &&
      ins->cal_ry.min == -7 && ins->cal_ry.center == 1504 &&
      ins->cal_ry.max == 3552) {
    logi(
        "Switch: Most probably using a Nintendo Swich clone controller. "
        "Overriding calibration values with default ones\n");
    ins->cal_x.min = ins->cal_y.min = ins->cal_rx.min = ins->cal_ry.min = 500;
    ins->cal_x.center = ins->cal_y.center = ins->cal_rx.center =
        ins->cal_ry.center = 2000;
    ins->cal_x.max = ins->cal_y.max = ins->cal_rx.max = ins->cal_ry.max = 3500;
  }

  logi(
      "Switch. Calibration info: x=%d,%d,%d, y=%d,%d,%d, rx=%d,%d,%d, "
      "ry=%d,%d,%d\n",
      ins->cal_x.min, ins->cal_x.center, ins->cal_x.max, ins->cal_y.min,
      ins->cal_y.center, ins->cal_y.max, ins->cal_rx.min, ins->cal_rx.center,
      ins->cal_rx.max, ins->cal_ry.min, ins->cal_ry.center, ins->cal_ry.max);
}

// Reply to SUBCMD_SET_LEDS
static void process_reply_set_leds(struct uni_hid_device_s* d,
                                   const struct switch_report_21_s* r,
                                   int len) {
  UNUSED(d);
  UNUSED(r);
  UNUSED(len);
}

// Reply SUBCMD_ENABLE_IMU
static void process_reply_enable_imu(struct uni_hid_device_s* d,
                                     const struct switch_report_21_s* r,
                                     int len) {
  UNUSED(d);
  UNUSED(r);
  UNUSED(len);
}

// Process 0x21 input report: SWITCH_INPUT_SUBCMD_REPLY
static void process_input_subcmd_reply(struct uni_hid_device_s* d,
                                       const uint8_t* report, int len) {
  // Report has this format:
  // 21 D9 80 08 10 00 18 A8 78 F2 C7 70 0C 80 30 00 00 00 00 00 00 00 00 00
  // 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  // 00
  const struct switch_report_21_s* r = (const struct switch_report_21_s*)report;
  if ((r->ack & 0b10000000) == 0) {
    loge("Switch: Error, subcommand id=0x%02x was not successful.\n",
         r->subcmd_id);
  }
  switch (r->subcmd_id) {
    case SUBCMD_REQ_DEV_INFO:
      process_reply_req_dev_info(d, r, len);
      break;
    case SUBCMD_SET_REPORT_MODE:
      process_reply_set_report_mode(d, r, len);
      break;
    case SUBCMD_SPI_FLASH_READ:
      process_reply_spi_flash_read(d, r, len);
      break;
    case SUBCMD_SET_LEDS:
      process_reply_set_leds(d, r, len);
      break;
    case SUBCMD_ENABLE_IMU:
      process_reply_enable_imu(d, r, len);
      break;
    default:
      loge("Switch: Error, unexpected subcmd_id=0x%02x in report 0x21\n",
           r->subcmd_id);
      break;
  }
  process_fsm(d);
}

// Process 0x30 input report: SWITCH_INPUT_IMU_DATA
static void process_input_imu_data(struct uni_hid_device_s* d,
                                   const uint8_t* report, int len) {
  // Expecting something like:
  // (a1) 30 44 60 00 00 00 FD 87 7B 0E B8 70 00 6C FD FC FF 78 10 35 00 C1 FF
  // 9D FF 72 FD 01 00 72 10 35 00 C1 FF 9B FF 75 FD FF FF 6C 10 34 00 C2 FF
  // 9A FF

  UNUSED(len);
  // printf_hexdump(report, len);
  // return;
  uni_gamepad_t* gp = &d->gamepad;
  const struct switch_report_30_s* r =
      (const struct switch_report_30_s*)&report[3];

  // Buttons "right"
  gp->buttons |= (r->buttons_right & 0b00000001) ? BUTTON_X : 0;           // Y
  gp->buttons |= (r->buttons_right & 0b00000010) ? BUTTON_Y : 0;           // X
  gp->buttons |= (r->buttons_right & 0b00000100) ? BUTTON_A : 0;           // B
  gp->buttons |= (r->buttons_right & 0b00001000) ? BUTTON_B : 0;           // A
  gp->buttons |= (r->buttons_right & 0b01000000) ? BUTTON_SHOULDER_R : 0;  // R
  gp->buttons |= (r->buttons_right & 0b10000000) ? BUTTON_TRIGGER_R : 0;   // ZR
  gp->updated_states |= GAMEPAD_STATE_BUTTON_A | GAMEPAD_STATE_BUTTON_B |
                        GAMEPAD_STATE_BUTTON_X | GAMEPAD_STATE_BUTTON_Y |
                        GAMEPAD_STATE_BUTTON_SHOULDER_R |
                        GAMEPAD_STATE_BUTTON_TRIGGER_R;

  // Buttons "misc" + thumbs
  gp->misc_buttons |=
      (r->buttons_misc & 0b00000001) ? MISC_BUTTON_BACK : 0;   // -
  gp->misc_buttons |= (r->buttons_misc & 0b00000010) ? 0 : 0;  // + (unused)
  gp->misc_buttons |=
      (r->buttons_misc & 0b00010000) ? MISC_BUTTON_SYSTEM : 0;  // Home
  gp->misc_buttons |=
      (r->buttons_misc & 0b00100000) ? MISC_BUTTON_HOME : 0;  // Circle
  gp->updated_states |= GAMEPAD_STATE_MISC_BUTTON_HOME |
                        GAMEPAD_STATE_MISC_BUTTON_SYSTEM |
                        GAMEPAD_STATE_MISC_BUTTON_BACK;
  gp->buttons |=
      (r->buttons_misc & 0b00000100) ? BUTTON_THUMB_R : 0;  // Thumb R
  gp->buttons |=
      (r->buttons_misc & 0b00001000) ? BUTTON_THUMB_L : 0;  // Thumb L
  gp->updated_states |=
      GAMEPAD_STATE_BUTTON_THUMB_L | GAMEPAD_STATE_BUTTON_THUMB_R;

  // Buttons "left"
  gp->dpad |= (r->buttons_left & 0b00000001) ? DPAD_DOWN : 0;
  gp->dpad |= (r->buttons_left & 0b00000010) ? DPAD_UP : 0;
  gp->dpad |= (r->buttons_left & 0b00000100) ? DPAD_RIGHT : 0;
  gp->dpad |= (r->buttons_left & 0b00001000) ? DPAD_LEFT : 0;
  gp->buttons |= (r->buttons_left & 0b01000000) ? BUTTON_SHOULDER_L : 0;  // L
  gp->buttons |= (r->buttons_left & 0b10000000) ? BUTTON_TRIGGER_L : 0;   // ZL
  gp->updated_states |= GAMEPAD_STATE_DPAD | GAMEPAD_STATE_BUTTON_SHOULDER_L |
                        GAMEPAD_STATE_BUTTON_TRIGGER_L;

  switch_instance_t* ins = get_switch_instance(d);
  // Stick left
  int16_t stick_lx = r->stick_left[0] | ((r->stick_left[1] & 0x0f) << 8);
  gp->axis_x = calibrate_axis(stick_lx, ins->cal_x);
  int16_t stick_ly = (r->stick_left[1] >> 4) | (r->stick_left[2] << 4);
  gp->axis_y = -calibrate_axis(stick_ly, ins->cal_y);

  // Stick right
  int16_t stick_rx = r->stick_right[0] | ((r->stick_right[1] & 0x0f) << 8);
  gp->axis_rx = calibrate_axis(stick_rx, ins->cal_rx);
  int16_t stick_ry = (r->stick_right[1] >> 4) | (r->stick_right[2] << 4);
  gp->axis_ry = -calibrate_axis(stick_ry, ins->cal_ry);

  gp->updated_states |= GAMEPAD_STATE_AXIS_X | GAMEPAD_STATE_AXIS_Y |
                        GAMEPAD_STATE_AXIS_RX | GAMEPAD_STATE_AXIS_RY;
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
  gp->buttons |= (r->buttons_main & 0b00000001) ? BUTTON_A : 0;           // B
  gp->buttons |= (r->buttons_main & 0b00000010) ? BUTTON_B : 0;           // A
  gp->buttons |= (r->buttons_main & 0b00000100) ? BUTTON_X : 0;           // Y
  gp->buttons |= (r->buttons_main & 0b00001000) ? BUTTON_Y : 0;           // X
  gp->buttons |= (r->buttons_main & 0b00010000) ? BUTTON_SHOULDER_L : 0;  // L
  gp->buttons |= (r->buttons_main & 0b00100000) ? BUTTON_SHOULDER_R : 0;  // R
  gp->buttons |= (r->buttons_main & 0b01000000) ? BUTTON_TRIGGER_L : 0;   // ZL
  gp->buttons |= (r->buttons_main & 0b10000000) ? BUTTON_TRIGGER_R : 0;   // ZR
  gp->updated_states |=
      GAMEPAD_STATE_BUTTON_A | GAMEPAD_STATE_BUTTON_B | GAMEPAD_STATE_BUTTON_X |
      GAMEPAD_STATE_BUTTON_Y | GAMEPAD_STATE_BUTTON_SHOULDER_L |
      GAMEPAD_STATE_BUTTON_SHOULDER_R | GAMEPAD_STATE_BUTTON_TRIGGER_L |
      GAMEPAD_STATE_BUTTON_TRIGGER_R;

  // Button aux
  gp->misc_buttons |=
      (r->buttons_aux & 0b00000001) ? MISC_BUTTON_BACK : 0;  // -
  gp->buttons |= (r->buttons_aux & 0b00000010) ? 0 : 0;      // + (unmapped)
  gp->buttons |= (r->buttons_aux & 0b00000100) ? BUTTON_THUMB_L : 0;  // Thumb L
  gp->buttons |= (r->buttons_aux & 0b00001000) ? BUTTON_THUMB_R : 0;  // Thumb R
  gp->misc_buttons |=
      (r->buttons_aux & 0b00010000) ? MISC_BUTTON_SYSTEM : 0;  // Home
  gp->misc_buttons |=
      (r->buttons_aux & 0b00100000) ? MISC_BUTTON_HOME : 0;  // Circle
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

static void fsm_request_device_info(struct uni_hid_device_s* d) {
  switch_instance_t* ins = get_switch_instance(d);
  ins->state = STATE_REQ_DEV_INFO;

  struct switch_subcmd_request req = {0};
  req.transaction_type = 0xa2;  // DATA | TYPE_OUTPUT
  req.report_id = 0x01;         // 0x01 for sub commands
  req.subcmd_id = SUBCMD_REQ_DEV_INFO;
  send_subcmd(d, &req, sizeof(req));
}

static void fsm_read_stick_calibration(struct uni_hid_device_s* d) {
  switch_instance_t* ins = get_switch_instance(d);
  ins->state = STATE_READ_STICK_CALIBRATION;

  uint8_t out[sizeof(struct switch_subcmd_request) + 5] = {0};
  struct switch_subcmd_request* req = (struct switch_subcmd_request*)&out[0];
  req->transaction_type = 0xa2;  // DATA | TYPE_OUTPUT
  req->report_id = 0x01;         // 0x01 for sub commands
  req->subcmd_id = SUBCMD_SPI_FLASH_READ;
  // Address to read from: stick calibration
  req->data[0] = SWITCH_CAL_DATA_ADDR & 0xff;
  req->data[1] = (SWITCH_CAL_DATA_ADDR >> 8) & 0xff;
  req->data[2] = (SWITCH_CAL_DATA_ADDR >> 16) & 0xff;
  req->data[3] = (SWITCH_CAL_DATA_ADDR >> 24) & 0xff;
  req->data[4] = SWITCH_CAL_DATA_SIZE;
  send_subcmd(d, req, sizeof(out));
}

static void fsm_set_full_report(struct uni_hid_device_s* d) {
  switch_instance_t* ins = get_switch_instance(d);
  ins->state = STATE_SET_FULL_REPORT;

  uint8_t out[sizeof(struct switch_subcmd_request) + 1] = {0};
  struct switch_subcmd_request* req = (struct switch_subcmd_request*)&out[0];
  req->transaction_type = 0xa2;  // DATA | TYPE_OUTPUT
  req->report_id = 0x01;         // 0x01 for sub commands
  req->subcmd_id = SUBCMD_SET_REPORT_MODE;
  req->data[0] = 0x30; /* type of report: standard, full */
  send_subcmd(d, req, sizeof(out));
}

static void fsm_enable_imu(struct uni_hid_device_s* d) {
  switch_instance_t* ins = get_switch_instance(d);
  ins->state = STATE_ENABLE_IMU;

  uint8_t out[sizeof(struct switch_subcmd_request) + 1] = {0};
  struct switch_subcmd_request* req = (struct switch_subcmd_request*)&out[0];
  req->transaction_type = 0xa2;  // DATA | TYPE_OUTPUT
  req->report_id = 0x01;         // 0x01 for sub commands
  req->subcmd_id = SUBCMD_ENABLE_IMU;
  req->data[0] = (ins->mode == SWITCH_MODE_ACCEL);
  send_subcmd(d, req, sizeof(out));
}

static void fsm_update_led(struct uni_hid_device_s* d) {
  switch_instance_t* ins = get_switch_instance(d);
  ins->state = STATE_READY;

  uint8_t out[sizeof(struct switch_subcmd_request) + 1] = {0};
  struct switch_subcmd_request* req = (struct switch_subcmd_request*)&out[0];
  req->transaction_type = 0xa2;  // DATA | TYPE_OUTPUT
  req->report_id = 0x01;         // 0x01 for sub commands
  req->subcmd_id = SUBCMD_SET_LEDS;
  req->data[0] = d->joystick_port;
  send_subcmd(d, req, sizeof(out));
}

void uni_hid_parser_switch_update_led(uni_hid_device_t* d) {
  switch_instance_t* ins = get_switch_instance(d);
  if (ins->state == STATE_UNINIT) {
    return;
  }

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

static int32_t calibrate_axis(int16_t v, switch_cal_stick_t cal) {
  int32_t ret;
  if (v > cal.center) {
    ret = (v - cal.center) * AXIS_NORMALIZE_RANGE / 2;
    ret /= (cal.max - cal.center);
  } else {
    ret = (cal.center - v) * -AXIS_NORMALIZE_RANGE / 2;
    ret /= (cal.center - cal.min);
  }
  // Clamp it
  ret = ret > (AXIS_NORMALIZE_RANGE / 2) ? (AXIS_NORMALIZE_RANGE / 2) : ret;
  ret = ret < -AXIS_NORMALIZE_RANGE / 2 ? -AXIS_NORMALIZE_RANGE / 2 : ret;
  return ret;
}
