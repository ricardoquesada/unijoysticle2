/****************************************************************************
http://retro.moe/unijoysticle

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

#ifndef UNI_HID_PARSER_H
#define UNI_HID_PARSER_H

#include <stdint.h>

#include "uni_hid_device.h"
#include "uni_gamepad.h"

// btstack bug:
// see: https://github.com/bluekitchen/btstack/issues/187
typedef struct hid_globals_s {
    int32_t         logical_minimum;
    int32_t         logical_maximum;
    uint16_t        usage_page;
    uint8_t         report_size;
    uint8_t         report_count;
    uint8_t         report_id;
} hid_globals_t;

uni_gamepad_t uni_hid_parser(const uint8_t* report, uint16_t report_len,
        const uint8_t* hid_descriptor, uint16_t hid_descriptor_len);
int32_t uni_hid_process_axis(hid_globals_t* globals, uint32_t value);
uint8_t uni_hid_process_hat(hid_globals_t* globals, uint32_t value);

void joystick_update(const uni_gamepad_t* gp, uni_joystick_port_t joy_port, uni_controller_type_t ctl_type);

#endif // UNI_HID_PARSER_H