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

#ifndef UNI_HID_PARSER_XBOXONE_H
#define UNI_HID_PARSER_XBOXONE_H

#include <stdint.h>

#include "btstack.h"

#include "uni_gamepad.h"
#include "uni_hid_parser.h"

// For Xbox One gamepads
void uni_hid_parser_xboxone_init(uni_gamepad_t* gamepad);
void uni_hid_parser_xboxone_parse_usage(uni_gamepad_t* gamepad,
                                        hid_globals_t* globals,
                                        uint16_t usage_page,
                                        uint16_t usage,
                                        int32_t value);

#endif  // UNI_HID_PARSER_XBOXONE_H