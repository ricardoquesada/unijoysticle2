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

#include "uni_hid_parser_icade.h"

#include "uni_debug.h"

void uni_hid_parser_icade(uni_gamepad_t* gamepad, hid_globals_t* globals, uint16_t usage_page, uint16_t usage, int32_t value) {
    UNUSED(globals);
    UNUSED(gamepad);
    logi("Unsupported page: 0x%04x, usage: 0x%04x, value=0x%x\n", usage_page, usage, value);
}