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

// For more info about Android mappings see:
// https://developer.android.com/training/game-controllers/controller-input

#include "uni_hid_parser_smarttvremote.h"

#include "uni_hid_parser.h"
#include "uni_debug.h"

void uni_hid_parser_smarttvremote_init(uni_gamepad_t* gamepad) {
    // Reset old state. Each report contains a full-state.
    gamepad->updated_states = 0;
}
void uni_hid_parser_smarttvremote_parse_usage(uni_gamepad_t* gamepad, hid_globals_t* globals, uint16_t usage_page, uint16_t usage, int32_t value) {
    UNUSED(globals);
    // print_parser_globals(globals);
    switch (usage_page) {
    case 0x01:  // Generic Desktop controls
        switch (usage) {
        case 0x90:  // dpad up
            if (value)
                gamepad->dpad |= DPAD_UP;
            else
                gamepad->dpad &= ~DPAD_UP;
            gamepad->updated_states |= GAMEPAD_STATE_DPAD;
            break;
        case 0x91:  // dpad down
            if (value)
                gamepad->dpad |= DPAD_DOWN;
            else
                gamepad->dpad &= ~DPAD_DOWN;
            gamepad->updated_states |= GAMEPAD_STATE_DPAD;
            break;
        case 0x92:  // dpad right
            if (value)
                gamepad->dpad |= DPAD_RIGHT;
            else
                gamepad->dpad &= ~DPAD_RIGHT;
            gamepad->updated_states |= GAMEPAD_STATE_DPAD;
            break;
        case 0x93:  // dpad left
            if (value)
                gamepad->dpad |= DPAD_LEFT;
            else
                gamepad->dpad &= ~DPAD_LEFT;
            gamepad->updated_states |= GAMEPAD_STATE_DPAD;
            break;
        default:
            logi("SmartTVRemote: Unsupported page: 0x%04x, usage: 0x%04x, value=0x%x\n", usage_page, usage, value);
            break;
        }
        break;
    case 0x06: // Generic Device Controls Page
        switch (usage) {
        case 0x20: // Battery Strength
            gamepad->battery = value;
            break;
        default:
            logi("SmartTVRemote: Unsupported page: 0x%04x, usage: 0x%04x, value=0x%x\n", usage_page, usage, value);
            break;
        }
        break;
    case 0x07:  // Keypad / Keyboard
        // FIXME: It is unlikely a device has both a dpap a keyboard, so we report certain keys
        // as dpad, just to avoid having a entry entry in the uni_gamepad_t type.
        switch (usage) {
        case 0x00:  // Reserved
            break;  // empty on purpose
        case 0x4f:  // Right arrow
            if (value)
                gamepad->dpad |= DPAD_RIGHT;
            else
                gamepad->dpad &= ~DPAD_RIGHT;
            gamepad->updated_states |= GAMEPAD_STATE_DPAD;
            break;
        case 0x50:  // Left arrow
            if (value)
                gamepad->dpad |= DPAD_LEFT;
            else
                gamepad->dpad &= ~DPAD_LEFT;
            gamepad->updated_states |= GAMEPAD_STATE_DPAD;
            break;
        case 0x51:  // Down arrow
            if (value)
                gamepad->dpad |= DPAD_DOWN;
            else
                gamepad->dpad &= ~DPAD_DOWN;
            gamepad->updated_states |= GAMEPAD_STATE_DPAD;
            break;
        case 0x52:  // Up arrow
            if (value)
                gamepad->dpad |= DPAD_UP;
            else
                gamepad->dpad &= ~DPAD_UP;
            gamepad->updated_states |= GAMEPAD_STATE_DPAD;
            break;
        case 0x58:  // Keypad enter
            if (value)
                gamepad->buttons |= BUTTON_A;
            else
                gamepad->buttons &= ~BUTTON_A;
            gamepad->updated_states |= GAMEPAD_STATE_BUTTON_A;
            break;
        case 0x66:  // Keypad power
            break;  // unmapped apparently
        case 0xf1:  // Back button (reserved)
            if (value)
                gamepad->misc_buttons |= MISC_BUTTON_BACK;
            else
                gamepad->misc_buttons &= ~MISC_BUTTON_BACK;
            gamepad->updated_states |= GAMEPAD_STATE_MISC_BUTTON_BACK;
            break;
        default:
            logi("SmartTVRemote: Unsupported page: 0x%04x, usage: 0x%04x, value=0x%x\n", usage_page, usage, value);
            break;
        }
        break;
    case 0x0c:  // Button
    {
        switch (usage) {
        case 0x40:      // menu
            if (value)
                gamepad->misc_buttons |= MISC_BUTTON_SYSTEM;
            else
                gamepad->misc_buttons &= ~MISC_BUTTON_SYSTEM;
            gamepad->updated_states |= GAMEPAD_STATE_MISC_BUTTON_SYSTEM;
            break;
        case 0x89:      // Media select tv
            break;
        case 0xb3:      // fast forward
            break;
        case 0xb4:      // rewind
            break;
        case 0xcd:      // play / pause
            break;
        case 0xe2:      // mute
            break;
        case 0xe9:      // vol up
            break;
        case 0xea:      // vol down
            break;
        case 0x0221:    // mic / search
            break;
        case 0x0223:    // home
            if (value)
                gamepad->misc_buttons |= MISC_BUTTON_HOME;
            else
                gamepad->misc_buttons &= ~MISC_BUTTON_HOME;
            gamepad->updated_states |= GAMEPAD_STATE_MISC_BUTTON_HOME;
            break;
        default:
            logi("SmartTVRemote: Unsupported page: 0x%04x, usage: 0x%04x, value=0x%x\n", usage_page, usage, value);
            break;
        }
        break;
    }
    // unknown usage page
    default:
            logi("SmartTVRemote: Unsupported page: 0x%04x, usage: 0x%04x, value=0x%x\n", usage_page, usage, value);
        break;
    }
}