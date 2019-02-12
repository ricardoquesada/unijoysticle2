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

#include "uni_hid_parser_apple.h"

#include "uni_hid_parser.h"
#include "uni_debug.h"

void uni_hid_parser_apple_init(uni_gamepad_t* gamepad) {
    // Reset old state. Each report contains a full-state.
    gamepad->updated_states = 0;
}

void uni_hid_parser_apple_parse_usage(uni_gamepad_t* gamepad, hid_globals_t* globals, uint16_t usage_page, uint16_t usage, int32_t value) {
    // print_parser_globals(globals);
    uint8_t hat;
    switch (usage_page) {
    case 0x01:  // Generic Desktop controls
        switch (usage) {
        case 0x30:  // x
            gamepad->axis_x = uni_hid_parser_process_axis(globals, value);
            gamepad->updated_states |= GAMEPAD_STATE_AXIS_X;
            break;
        case 0x31:  // y
            // iOS devices seems to have axis Y inverted
            gamepad->axis_y = -uni_hid_parser_process_axis(globals, value);
            gamepad->updated_states |= GAMEPAD_STATE_AXIS_Y;
            break;
        case 0x32:  // z
            gamepad->axis_rx = uni_hid_parser_process_axis(globals, value);
            gamepad->updated_states |= GAMEPAD_STATE_AXIS_RX;
            break;
        case 0x35:  // rz
            gamepad->axis_ry = -uni_hid_parser_process_axis(globals, value);
            gamepad->updated_states |= GAMEPAD_STATE_AXIS_RY;
            break;
        case 0x39:  // switch hat
            hat = uni_hid_parser_process_hat(globals, value);
            gamepad->dpad = uni_hid_parser_hat_to_dpad(hat);
            gamepad->updated_states |= GAMEPAD_STATE_DPAD;
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
            logi("Apple: Unsupported page: 0x%04x, usage: 0x%04x, value=0x%x\n", usage_page, usage, value);
            break;
        }
        break;
    case 0x02:  // Simulation controls
        switch (usage) {
        case 0xc4:  // accelerator
            gamepad->accelerator = uni_hid_parser_process_pedal(globals, value);
            gamepad->updated_states |= GAMEPAD_STATE_ACCELERATOR;
            break;
        case 0xc5:  // brake
            gamepad->brake =  uni_hid_parser_process_pedal(globals, value);
            gamepad->updated_states |= GAMEPAD_STATE_BRAKE;
            break;
        default:
            logi("Apple: Unsupported page: 0x%04x, usage: 0x%04x, value=0x%x\n", usage_page, usage, value);
            break;
        };
        break;
    case 0x06: // Generic Device Controls Page
        switch (usage) {
        case 0x20: // Battery Strength
            gamepad->battery = value;
            break;
        default:
            logi("Apple: Unsupported page: 0x%04x, usage: 0x%04x, value=0x%x\n", usage_page, usage, value);
            break;
        }
        break;

    case 0x09:  // Button
    {
        // we start with usage - 1 since "button 0" seems that is not being used
        // and we only support 32 buttons.
        uint16_t button_idx = usage-1;
        if (button_idx < BUTTON_TOTAL) {
            if (value)
                gamepad->buttons |= (BUTTON_A << button_idx);
            else
                gamepad->buttons &= ~(BUTTON_A << button_idx);
            gamepad->updated_states |= (GAMEPAD_STATE_BUTTON_A << button_idx);
        } else {
            logi("Apple: Unsupported page: 0x%04x, usage: 0x%04x, value=0x%x\n", usage_page, usage, value);
        }
        break;
    }
    case 0x0c:  // Consumer
        switch (usage) {
        case 0x221:     // search
            break;
        case 0x0223:    // home
            if (value)
                gamepad->misc_buttons |= MISC_BUTTON_SYSTEM;
            else
                gamepad->misc_buttons &= ~MISC_BUTTON_SYSTEM;
            gamepad->updated_states |= GAMEPAD_STATE_MISC_BUTTON_SYSTEM;
            break;
        case 0x0224:    // back
            break;
        default:
            logi("Apple: Unsupported page: 0x%04x, usage: 0x%04x, value=0x%x\n", usage_page, usage, value);
            break;
        }
        break;

    // unknown usage page
    default:
            logi("Apple: Unsupported page: 0x%04x, usage: 0x%04x, value=0x%x\n", usage_page, usage, value);
        break;
    }
}