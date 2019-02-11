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

    logi("OUYA: usage page=0x%04x, page=0x%04x, value=0x%04x\n", usage_page, usage, value);

    switch (usage_page) {
    case 1: // Generic Desktop Page (0x01)
        switch(usage) {
        case 0x30:      // Axis X
        case 0x31:      // Axis Y
        case 0x32:      // Axis Z
        case 0x33:      // Axis RX
        case 0x34:      // Axis RY
        case 0x35:      // Axis RZ
        default:
            break;
        }
        break;
    case 9: // Button Page (0x09)
        switch(usage) {
        case 1:
            if (value)
                gamepad->buttons |= (1 << 0);
            else gamepad->buttons &= ~(1 << 0);
            gamepad->updated_states |= GAMEPAD_STATE_BUTTON_A;
            break;
        case 2:
        case 3:
        case 4:
            break;
        case 9:
            if (value)
                gamepad->dpad |= DPAD_UP;
            else gamepad->dpad &= ~DPAD_UP;
            gamepad->updated_states |= GAMEPAD_STATE_DPAD;
            break;
        case 0x0a:
            if (value)
                gamepad->dpad |= DPAD_DOWN;
            else gamepad->dpad &= ~DPAD_DOWN;
            gamepad->updated_states |= GAMEPAD_STATE_DPAD;
            break;
        case 0x0b:
            if (value)
                gamepad->dpad |= DPAD_LEFT;
            else gamepad->dpad &= ~DPAD_LEFT;
            gamepad->updated_states |= GAMEPAD_STATE_DPAD;
            break;
        case 0x0c:
            if (value)
                gamepad->dpad |= DPAD_RIGHT;
            else gamepad->dpad &= ~DPAD_RIGHT;
            gamepad->updated_states |= GAMEPAD_STATE_DPAD;
            break;
        }
        break;
    default:
        logi("OUYA: usage page=0x%04x, page=0x%04x, value=0x%04x\n", usage_page, usage, value);
        break;
    }
}