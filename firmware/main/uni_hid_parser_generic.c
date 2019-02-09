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

#include "uni_hid_parser_generic.h"

#include "uni_hid_parser.h"
#include "uni_debug.h"

void uni_hid_parser_generic(uni_gamepad_t* gamepad, hid_globals_t* globals, uint16_t usage_page, uint16_t usage, int32_t value) {
    // print_parser_globals(globals);
    switch (usage_page) {
    case 0x01:  // Generic Desktop controls
        switch (usage) {
        case 0x30:  // x
            gamepad->x = uni_hid_process_axis(globals, value);
            gamepad->updated_states |= GAMEPAD_STATE_X;
            break;
        case 0x31:  // y
            gamepad->y = uni_hid_process_axis(globals, value);
            gamepad->updated_states |= GAMEPAD_STATE_Y;
            break;
        case 0x32:  // z
            gamepad->z = uni_hid_process_axis(globals, value);
            gamepad->updated_states |= GAMEPAD_STATE_Z;
            break;
        case 0x33:  // rx
            gamepad->rx = uni_hid_process_axis(globals, value);
            gamepad->updated_states |= GAMEPAD_STATE_RX;
            break;
        case 0x34:  // ry
            gamepad->ry = uni_hid_process_axis(globals, value);
            gamepad->updated_states |= GAMEPAD_STATE_RY;
            break;
        case 0x35:  // rz
            gamepad->rz = uni_hid_process_axis(globals, value);
            gamepad->updated_states |= GAMEPAD_STATE_RZ;
            break;
        case 0x39:  // switch hat
            gamepad->hat = uni_hid_process_hat(globals, value);
            gamepad->updated_states |= GAMEPAD_STATE_HAT;
            break;
        case 0x85: // system main menu
            if (value)
                gamepad->misc_buttons |= MISC_SYS_MAIN_MENU;
            else
                gamepad->misc_buttons &= ~MISC_SYS_MAIN_MENU;
            break;
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
            logi("Unsupported page: 0x%04x, usage: 0x%04x, value=0x%x\n", usage_page, usage, value);
            break;
        }
        break;
    case 0x02:  // Simulation controls
        switch (usage) {
        case 0xc4:  // accelerator
            gamepad->accelerator = value;
            gamepad->updated_states |= GAMEPAD_STATE_ACCELERATOR;
            break;
        case 0xc5:  // brake
            gamepad->brake = value;
            gamepad->updated_states |= GAMEPAD_STATE_BRAKE;
            break;
        default:
            logi("Unsupported page: 0x%04x, usage: 0x%04x, value=0x%x\n", usage_page, usage, value);
            break;
        };
        break;
    case 0x06: // Generic Device Controls Page
        switch (usage) {
        case 0x20: // Battery Strength
            gamepad->battery = value;
            break;
        default:
            logi("Unsupported page: 0x%04x, usage: 0x%04x, value=0x%x\n", usage_page, usage, value);
            break;
        }
        break;
    case 0x07:  // Keypad / Keyboard
        // FIXME: It is unlikely a device has both a dpap a keyboard, so we report certain keys
        // as dpad, just to avoid having a entry entry in the uni_gamepad_t type.
        switch (usage) {
        case 0x00:  // Reserved
            // empty on purpose
            break;
        case 0x4f:  // Right arrow
        case 0x5e:  // Keypad right arrow
            if (value)
                gamepad->dpad |= DPAD_RIGHT;
            else
                gamepad->dpad &= ~DPAD_RIGHT;
            gamepad->updated_states |= GAMEPAD_STATE_DPAD;
            break;
        case 0x50:  // Left arrow
        case 0x5c:  // Keypad left arrow
            if (value)
                gamepad->dpad |= DPAD_LEFT;
            else
                gamepad->dpad &= ~DPAD_LEFT;
            gamepad->updated_states |= GAMEPAD_STATE_DPAD;
            break;
        case 0x51:  // Down arrow
        case 0x5a:  // Keypad down arrow
            if (value)
                gamepad->dpad |= DPAD_DOWN;
            else
                gamepad->dpad &= ~DPAD_DOWN;
            gamepad->updated_states |= GAMEPAD_STATE_DPAD;
            break;
        case 0x52:  // Up arrow
        case 0x60:  // Keypad up arrow
            if (value)
                gamepad->dpad |= DPAD_UP;
            else
                gamepad->dpad &= ~DPAD_UP;
            gamepad->updated_states |= GAMEPAD_STATE_DPAD;
            break;
        case 0x1d:  // z
        case 0x28:  // Enter
        case 0x2c:  // spacebar
        case 0x58:  // Keypad enter
            if (value)
                gamepad->buttons |= (1 << 0);
            else
                gamepad->buttons &= ~(1 << 0);
            gamepad->updated_states |= GAMEPAD_STATE_BUTTON0;
            break;
        default:
            logi("Unsupported page: 0x%04x, usage: 0x%04x, value=0x%x\n", usage_page, usage, value);
            break;
        }
        break;
    case 0x09:  // Button
    {
        // we start with usage - 1 since "button 0" seems that is not being used
        // and we only support 32 buttons.
        uint16_t button_idx = usage-1;
        if (button_idx < 16) {
            if (value)
                gamepad->buttons |= (1 << button_idx);
            else
                gamepad->buttons &= ~(1 << button_idx);
            gamepad->updated_states |= (GAMEPAD_STATE_BUTTON0 << button_idx);
        } else {
            logi("Unsupported page: 0x%04x, usage: 0x%04x, value=0x%x\n", usage_page, usage, value);
        }
        break;
    }
    case 0x0c:  // Consumer
        switch (usage) {
        case 0x221:     // search
            if (value)
                gamepad->misc_buttons |= MISC_AC_SEARCH;
            else
                gamepad->misc_buttons &= ~MISC_AC_SEARCH;
        case 0x0223:    // home
            if (value)
                gamepad->misc_buttons |= MISC_AC_HOME;
            else
                gamepad->misc_buttons &= ~MISC_AC_HOME;
            break;
        case 0x0224:    // back
            if (value)
                gamepad->misc_buttons |= MISC_AC_BACK;
            else
                gamepad->misc_buttons &= ~MISC_AC_BACK;
            break;
        default:
            logi("Unsupported page: 0x%04x, usage: 0x%04x, value=0x%x\n", usage_page, usage, value);
            break;
        }
        break;

    // unknown usage page
    default:
            logi("Unsupported page: 0x%04x, usage: 0x%04x, value=0x%x\n", usage_page, usage, value);
        break;
    }
}