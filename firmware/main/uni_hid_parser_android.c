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

#include "uni_hid_parser_android.h"

#include "uni_debug.h"
#include "uni_hid_parser.h"

void uni_hid_parser_android_init(uni_gamepad_t* gamepad) {
  // Reset old state. Each report contains a full-state.
  gamepad->updated_states = 0;
}

void uni_hid_parser_android_parse_usage(uni_gamepad_t* gamepad,
                                        hid_globals_t* globals,
                                        uint16_t usage_page,
                                        uint16_t usage,
                                        int32_t value) {
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
          gamepad->axis_y = uni_hid_parser_process_axis(globals, value);
          gamepad->updated_states |= GAMEPAD_STATE_AXIS_Y;
          break;
        case 0x32:  // z
          gamepad->axis_rx = uni_hid_parser_process_axis(globals, value);
          gamepad->updated_states |= GAMEPAD_STATE_AXIS_RX;
          break;
        case 0x35:  // rz
          gamepad->axis_ry = uni_hid_parser_process_axis(globals, value);
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
          logi("Android: Unsupported page: 0x%04x, usage: 0x%04x, value=0x%x\n", usage_page, usage, value);
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
          gamepad->brake = uni_hid_parser_process_pedal(globals, value);
          gamepad->updated_states |= GAMEPAD_STATE_BRAKE;
          break;
        default:
          logi("Android: Unsupported page: 0x%04x, usage: 0x%04x, value=0x%x\n", usage_page, usage, value);
          break;
      };
      break;
    case 0x06:  // Generic Device Controls Page
      switch (usage) {
        case 0x20:  // Battery Strength
          gamepad->battery = value;
          break;
        default:
          logi("Android: Unsupported page: 0x%04x, usage: 0x%04x, value=0x%x\n", usage_page, usage, value);
          break;
      }
      break;
    case 0x09:  // Button
    {
      // Start with usage - 1 since "button 0" seems that is not being used.
      if (usage <= 9) {
        uint16_t button_idx = usage - 1;
        if (value)
          gamepad->buttons |= (BUTTON_A << button_idx);
        else
          gamepad->buttons &= ~(BUTTON_A << button_idx);
        gamepad->updated_states |= (GAMEPAD_STATE_BUTTON_A << button_idx);
        break;
      }
      switch (usage) {
        case 0x0a:  // unsupported misc button
        case 0x0b:  // unsupported misc button
        case 0x0c:  // unsupported misc button
          break;
        case 0x0d:
          if (value)
            gamepad->misc_buttons |= MISC_BUTTON_SYSTEM;
          else
            gamepad->misc_buttons &= ~MISC_BUTTON_SYSTEM;
          gamepad->updated_states |= GAMEPAD_STATE_MISC_BUTTON_SYSTEM;
          break;
        case 0x0e:
          if (value)
            gamepad->buttons |= BUTTON_THUMB_L;
          else
            gamepad->buttons &= ~BUTTON_THUMB_L;
          gamepad->updated_states |= GAMEPAD_STATE_BUTTON_THUMB_L;
          break;
        case 0x0f:
          if (value)
            gamepad->buttons |= BUTTON_THUMB_R;
          else
            gamepad->buttons &= ~BUTTON_THUMB_R;
          gamepad->updated_states |= GAMEPAD_STATE_BUTTON_THUMB_R;
          break;
        default:
          logi("Android: Unsupported page: 0x%04x, usage: 0x%04x, value=0x%x\n", usage_page, usage, value);
          break;
      }
      break;
    }
    case 0x0c:  // Consumer
      switch (usage) {
        case 0xb3:  // fast forward
          break;
        case 0xb4:  // rewind
          break;
        case 0xcd:  // play / pause
          break;
        case 0x221:  // search
          break;
        case 0x0223:  // home
          if (value)
            gamepad->misc_buttons |= MISC_BUTTON_HOME;
          else
            gamepad->misc_buttons &= ~MISC_BUTTON_HOME;
          gamepad->updated_states |= GAMEPAD_STATE_MISC_BUTTON_HOME;
          break;
        case 0x0224:  // back
          if (value)
            gamepad->misc_buttons |= MISC_BUTTON_BACK;
          else
            gamepad->misc_buttons &= ~MISC_BUTTON_BACK;
          gamepad->updated_states |= GAMEPAD_STATE_MISC_BUTTON_BACK;
          break;
        default:
          logi("Android: Unsupported page: 0x%04x, usage: 0x%04x, value=0x%x\n", usage_page, usage, value);
          break;
      }
      break;

    // unknown usage page
    default:
      logi("Android: Unsupported page: 0x%04x, usage: 0x%04x, value=0x%x\n", usage_page, usage, value);
      break;
  }
}