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

#include "uni_hid_parser_wiiupro.h"

#include "hid_usage.h"
#include "uni_debug.h"
#include "uni_hid_device.h"
#include "uni_hid_parser.h"

static uni_hid_device_t* g_device = NULL;
void uni_hid_parser_wiiupro_setup(uni_hid_device_t* d) {
  g_device = d;
  const uint8_t led_report[] = {0xa2, 0x15, 0x00};
  logi("Wii U Pro: sending DRM set report\n");
  log_info("Wii U Pro: sending DRM set report");
  uni_hid_device_send_report(d, led_report, sizeof(led_report));

  // const uint8_t led_report1[] = {0xa2, 0x12, 0x00, 0x30};
  // uni_hid_device_send_report(d, led_report1, sizeof(led_report1));
  // log_info("**** sending auth requested ****");
  // hci_send_cmd(&hci_authentication_requested, d->con_handle);
}

void uni_hid_parser_wiiupro_init_report(uni_gamepad_t* gp) {
  // Reset old state. Each report contains a full-state.
  gp->updated_states = 0;
  log_info("Nintendo Wii U Pro controller not supported yet");
}

void uni_hid_parser_wiiupro_parse_raw(uni_gamepad_t* gp, const uint8_t* report,
                                      uint16_t len) {
  UNUSED(gp);
  UNUSED(len);
  if (!g_device) {
    return;
  }
  switch (report[0]) {
    case 0x20: {
      const uint8_t r[] = {0xa2, 0x12, 0x00, 0x30};
      uni_hid_device_send_report(g_device, r, sizeof(r));
      break;
    }

    case 0x30: {
      const uint8_t r[] = {0xa2, 0x16, 0x04, 0xa4, 0x00, 0xf0, 0x01, 0x55,
                           00,   00,   00,   00,   00,   00,   00,   00,
                           00,   00,   00,   00,   00,   00,   00};
      uni_hid_device_send_report(g_device, r, sizeof(r));
      break;
    }

    case 0x22: {
      const uint8_t r[] = {0xa2, 0x11, 0x01};
      uni_hid_device_send_report(g_device, r, sizeof(r));
      break;
    }
  }
}