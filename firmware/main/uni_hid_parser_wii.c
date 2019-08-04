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

/* Protocol info taken from:
   https://github.com/dvdhrm/xwiimote/blob/master/doc/PROTOCOL
 */

#include "uni_hid_parser_wii.h"

#include "hid_usage.h"
#include "uni_debug.h"
#include "uni_hid_device.h"
#include "uni_hid_parser.h"

// Taken from Linux kernel: hid-wiimote.h
enum wiiproto_reqs {
  WIIPROTO_REQ_NULL = 0x0,
  WIIPROTO_REQ_RUMBLE = 0x10,
  WIIPROTO_REQ_LED = 0x11,
  WIIPROTO_REQ_DRM = 0x12,
  WIIPROTO_REQ_IR1 = 0x13,
  WIIPROTO_REQ_SREQ = 0x15,
  WIIPROTO_REQ_WMEM = 0x16,
  WIIPROTO_REQ_RMEM = 0x17,
  WIIPROTO_REQ_IR2 = 0x1a,
  WIIPROTO_REQ_STATUS = 0x20,
  WIIPROTO_REQ_DATA = 0x21,
  WIIPROTO_REQ_RETURN = 0x22,

  /* DRM_K: BB*2 */
  WIIPROTO_REQ_DRM_K = 0x30,

  /* DRM_KA: BB*2 AA*3 */
  WIIPROTO_REQ_DRM_KA = 0x31,

  /* DRM_KE: BB*2 EE*8 */
  WIIPROTO_REQ_DRM_KE = 0x32,

  /* DRM_KAI: BB*2 AA*3 II*12 */
  WIIPROTO_REQ_DRM_KAI = 0x33,

  /* DRM_KEE: BB*2 EE*19 */
  WIIPROTO_REQ_DRM_KEE = 0x34,

  /* DRM_KAE: BB*2 AA*3 EE*16 */
  WIIPROTO_REQ_DRM_KAE = 0x35,

  /* DRM_KIE: BB*2 II*10 EE*9 */
  WIIPROTO_REQ_DRM_KIE = 0x36,

  /* DRM_KAIE: BB*2 AA*3 II*10 EE*6 */
  WIIPROTO_REQ_DRM_KAIE = 0x37,

  /* DRM_E: EE*21 */
  WIIPROTO_REQ_DRM_E = 0x3d,

  /* DRM_SKAI1: BB*2 AA*1 II*18 */
  WIIPROTO_REQ_DRM_SKAI1 = 0x3e,

  /* DRM_SKAI2: BB*2 AA*1 II*18 */
  WIIPROTO_REQ_DRM_SKAI2 = 0x3f,

  WIIPROTO_REQ_MAX
};

static void process_drm_k(uni_gamepad_t* gp, const uint8_t* report,
                          uint16_t len);
static void process_drm_kee(uni_gamepad_t* gp, const uint8_t* report,
                            uint16_t len);
static void request_report(uni_hid_device_t* d);

void uni_hid_parser_wii_setup(uni_hid_device_t* d) {
  // Set LED to 1.
  const uint8_t led[] = {0xa2, WIIPROTO_REQ_LED, 0x10 /* LED 1 */};
  uni_hid_device_send_report(d, led, sizeof(led));

  // Just in case, we request the status report:
  const uint8_t status[] = {0xa2, WIIPROTO_REQ_SREQ, 0x00 /* rumble off */};
  uni_hid_device_send_report(d, status, sizeof(status));
}

void uni_hid_parser_wii_init_report(uni_gamepad_t* gp) {
  // Reset old state. Each report contains a full-state.
  gp->updated_states = 0;
  gp->dpad = 0;
  gp->buttons = 0;
  gp->misc_buttons = 0;
}

void uni_hid_parser_wii_parse_raw(uni_hid_device_t* d, const uint8_t* report,
                                  uint16_t len) {
  if (len == 0) return;
  switch (report[0]) {
    case WIIPROTO_REQ_STATUS:
      logi("Nintendo Wii: Status report: ");
      printf_hexdump(report, len);
      request_report(d);
      break;
    case WIIPROTO_REQ_DRM_K:
      process_drm_k(&d->gamepad, report, len);
      break;
    case WIIPROTO_REQ_DRM_KEE:
      process_drm_kee(&d->gamepad, report, len);
      break;
    default:
      logi("Wii parser: unknown report type: 0x%02x\n", report[0]);
      printf_hexdump(report, len);
  }
}
static void process_drm_k(uni_gamepad_t* gp, const uint8_t* report,
                          uint16_t len) {
  /* DRM_K: BB*2 */
  // Expecting something like:
  // 30 00 08
  if (len < 3) {
    loge("wii remote parser: invalid report len %d\n", len);
    return;
  }

  const uint8_t* data = &report[1];

  // dpad
  gp->dpad |= (data[0] & 0x01) ? DPAD_LEFT : 0;
  gp->dpad |= (data[0] & 0x02) ? DPAD_RIGHT : 0;
  gp->dpad |= (data[0] & 0x04) ? DPAD_DOWN : 0;
  gp->dpad |= (data[0] & 0x08) ? DPAD_UP : 0;
  gp->updated_states |= GAMEPAD_STATE_DPAD;

  // buttons
  gp->buttons |= (data[1] & 0x04) ? BUTTON_A : 0;  // Shoulder button
  gp->buttons |= (data[1] & 0x08) ? BUTTON_B : 0;  // Big button "A"
  gp->buttons |= (data[1] & 0x02) ? BUTTON_X : 0;  // Button "1"
  gp->buttons |= (data[1] & 0x01) ? BUTTON_Y : 0;  // Button "2"
  gp->updated_states |= GAMEPAD_STATE_BUTTON_A | GAMEPAD_STATE_BUTTON_B |
                        GAMEPAD_STATE_BUTTON_X | GAMEPAD_STATE_BUTTON_Y;

  // Process misc buttons
  gp->misc_buttons |= !(data[1] & 0x80) ? MISC_BUTTON_SYSTEM : 0;
  gp->misc_buttons |= !(data[0] & 0x10) ? MISC_BUTTON_HOME : 0;  // Button "+"
  gp->updated_states |=
      GAMEPAD_STATE_MISC_BUTTON_SYSTEM | GAMEPAD_STATE_MISC_BUTTON_HOME;
}

static void process_drm_kee(uni_gamepad_t* gp, const uint8_t* report,
                            uint16_t len) {
  /* DRM_KEE: BB*2 EE*19 */
  // Expecting something like:
  // 34 00 00 19 08 D5 07 20 08 21 08 FF FF CF 00 00 00 00 00 00 00 00

  // Doc taken from hid-wiimote-modules.c from Linux Kernel

  /*   Byte |  8  |  7  |  6  |  5  |  4  |  3  |  2  |  1  |
   *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
   *    0   |                   LX <7:0>                    |
   *   -----+-----------------------+-----------------------+
   *    1   |  0     0     0     0  |       LX <11:8>       |
   *   -----+-----------------------+-----------------------+
   *    2   |                   RX <7:0>                    |
   *   -----+-----------------------+-----------------------+
   *    3   |  0     0     0     0  |       RX <11:8>       |
   *   -----+-----------------------+-----------------------+
   *    4   |                   LY <7:0>                    |
   *   -----+-----------------------+-----------------------+
   *    5   |  0     0     0     0  |       LY <11:8>       |
   *   -----+-----------------------+-----------------------+
   *    6   |                   RY <7:0>                    |
   *   -----+-----------------------+-----------------------+
   *    7   |  0     0     0     0  |       RY <11:8>       |
   *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
   *    8   | BDR | BDD | BLT | B-  | BH  | B+  | BRT |  1  |
   *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
   *    9   | BZL | BB  | BY  | BA  | BX  | BZR | BDL | BDU |
   *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
   *   10   |  1  |     BATTERY     | USB |CHARG|LTHUM|RTHUM|
   *   -----+-----+-----------------+-----------+-----+-----+
   * All buttons are low-active (0 if pressed)
   * RX and RY are right analog stick
   * LX and LY are left analog stick
   * BLT is left trigger, BRT is right trigger.
   * BDR, BDD, BDL, BDU form the D-Pad with right, down, left, up buttons
   * BZL is left Z button and BZR is right Z button
   * B-, BH, B+ are +, HOME and - buttons
   * BB, BY, BA, BX are A, B, X, Y buttons
   *
   * Bits marked as 0/1 are unknown and never changed during tests.
   *
   * Not entirely verified:
   *   CHARG: 1 if uncharging, 0 if charging
   *   USB: 1 if not connected, 0 if connected
   *   BATTERY: battery capacity from 000 (empty) to 100 (full)
   */
  if (len < 14) {
    loge("wii u pro parser: invalid report len %d\n", len);
    return;
  }

  const uint8_t* data = &report[3];

  // Process axis
  const uint16_t axis_base = 0x800;
  // const uint16_t axis_range = 0x500;
  int16_t lx = data[0] + ((data[1] & 0x0f) << 8) - axis_base;
  int16_t rx = data[2] + ((data[3] & 0x0f) << 8) - axis_base;
  int16_t ly = data[4] + ((data[5] & 0x0f) << 8) - axis_base;
  int16_t ry = data[6] + ((data[7] & 0x0f) << 8) - axis_base;

  // Y is inverted
  gp->axis_x = lx;
  gp->axis_y = -ly;
  gp->axis_rx = rx;
  gp->axis_ry = -ry;
  gp->updated_states |= GAMEPAD_STATE_AXIS_X | GAMEPAD_STATE_AXIS_Y |
                        GAMEPAD_STATE_AXIS_RX | GAMEPAD_STATE_AXIS_RY;

  // Process Dpad
  gp->dpad |= !(data[8] & 0x80) ? DPAD_RIGHT : 0;  // BDR
  gp->dpad |= !(data[8] & 0x40) ? DPAD_DOWN : 0;   // BDD
  gp->dpad |= !(data[9] & 0x02) ? DPAD_LEFT : 0;   // BDL
  gp->dpad |= !(data[9] & 0x01) ? DPAD_UP : 0;     // BDU
  gp->updated_states |= GAMEPAD_STATE_DPAD;

  // Process buttons. A,B -> B,A; X,Y -> Y,X; trigger <--> shoulder
  gp->buttons |= !(data[9] & 0x10) ? BUTTON_B : 0;           // BA
  gp->buttons |= !(data[9] & 0x40) ? BUTTON_A : 0;           // BB
  gp->buttons |= !(data[9] & 0x08) ? BUTTON_Y : 0;           // BX
  gp->buttons |= !(data[9] & 0x20) ? BUTTON_X : 0;           // BY
  gp->buttons |= !(data[9] & 0x80) ? BUTTON_TRIGGER_L : 0;   // BZL
  gp->buttons |= !(data[9] & 0x04) ? BUTTON_TRIGGER_R : 0;   // BZR
  gp->buttons |= !(data[8] & 0x20) ? BUTTON_SHOULDER_L : 0;  // BLT
  gp->buttons |= !(data[8] & 0x02) ? BUTTON_SHOULDER_R : 0;  // BRT
  gp->buttons |= !(data[10] & 0x02) ? BUTTON_THUMB_L : 0;    // LTHUM
  gp->buttons |= !(data[10] & 0x01) ? BUTTON_THUMB_R : 0;    // RTHUM
  gp->updated_states |=
      GAMEPAD_STATE_BUTTON_SHOULDER_L | GAMEPAD_STATE_BUTTON_SHOULDER_R |
      GAMEPAD_STATE_BUTTON_TRIGGER_L | GAMEPAD_STATE_BUTTON_TRIGGER_R |
      GAMEPAD_STATE_BUTTON_A | GAMEPAD_STATE_BUTTON_B | GAMEPAD_STATE_BUTTON_X |
      GAMEPAD_STATE_BUTTON_Y | GAMEPAD_STATE_BUTTON_THUMB_L |
      GAMEPAD_STATE_BUTTON_THUMB_R;

  // Process misc buttons
  gp->misc_buttons |= !(data[8] & 0x08) ? MISC_BUTTON_SYSTEM : 0;  // BH
  gp->misc_buttons |= !(data[8] & 0x04) ? MISC_BUTTON_HOME : 0;    // B+
  gp->updated_states |=
      GAMEPAD_STATE_MISC_BUTTON_SYSTEM | GAMEPAD_STATE_MISC_BUTTON_HOME;
}

void static request_report(uni_hid_device_t* d) {
  // FIXME: Instead of hardcoding the types of reports, I should query flags
  // and based on that request the correct report.
  if (d->product_id == 0x306 /* wii remote */) {
    // 0x30 WIIPROTO_REQ_DRM_K (present in Wii Remote)
    const uint8_t reportK[] = {0xa2, WIIPROTO_REQ_DRM, 0x00,
                               WIIPROTO_REQ_DRM_K};
    uni_hid_device_send_report(d, reportK, sizeof(reportK));
  } else if (d->product_id == 0x0330 /* wii u pro */) {
    // 0x34 WIIPROTO_REQ_DRM_KEE (present in Wii U Pro controller)
    const uint8_t reportKee[] = {0xa2, WIIPROTO_REQ_DRM, 0x00,
                                 WIIPROTO_REQ_DRM_KEE};
    uni_hid_device_send_report(d, reportKee, sizeof(reportKee));
  }
}
