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

void uni_hid_parser_wiiupro_setup(void* device /* uni_hid_device_t */) {
  const uint8_t led_report[] = {0x52, 0x15, 0xff};
  log_info("Wii U Pro: sending LED report");
  uni_hid_device_send_report(device, led_report, sizeof(led_report));
}

void uni_hid_parser_wiiupro_init_report(uni_gamepad_t* gp) {
  // Reset old state. Each report contains a full-state.
  gp->updated_states = 0;
  log_info("Nintendo Wii U Pro controller not supported yet");
}

void uni_hid_parser_wiiupro_parse_raw(uni_gamepad_t* gp, const uint8_t* report,
                                      uint16_t len) {
  UNUSED(gp);
  UNUSED(report);
  UNUSED(len);
}