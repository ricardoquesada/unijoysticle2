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

#include "uni_hid_parser_ouya.h"

#include "uni_debug.h"

void uni_hid_parser_ouya_init(uni_gamepad_t* gamepad) {
    // Reset old state. Each report contains a full-state.
    gamepad->updated_states = 0;
}

void uni_hid_parser_ouya_parse_usage(uni_gamepad_t* gamepad, hid_globals_t* globals, uint16_t usage_page, uint16_t usage, int32_t value) {
    UNUSED(gamepad);
    UNUSED(globals);
    UNUSED(usage_page);
    UNUSED(usage);
    UNUSED(value);
}