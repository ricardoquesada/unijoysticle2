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

#include "hid_usage.h"
#include "uni_debug.h"
#include "uni_hid_parser.h"

void uni_hid_parser_smarttvremote_init(uni_gamepad_t* gamepad) {
  // Reset old state. Each report contains a full-state.
  gamepad->updated_states = 0;
}
void uni_hid_parser_smarttvremote_parse_usage(uni_gamepad_t* gamepad,
                                              hid_globals_t* globals,
                                              uint16_t usage_page,
                                              uint16_t usage,
                                              int32_t value) {
  UNUSED(globals);
  // print_parser_globals(globals);
  switch (usage_page) {
    case HID_USAGE_PAGE_GENERIC_DEVICE_CONTROLS:
      switch (usage) {
        case HID_USAGE_BATTERY_STRENGHT:
          gamepad->battery = value;
          break;
        default:
          logi("SmartTVRemote: Unsupported page: 0x%04x, usage: 0x%04x, value=0x%x\n", usage_page, usage, value);
          break;
      }
      break;
    case HID_USAGE_PAGE_KEYBOARD_KEYPAD:
      // FIXME: It is unlikely a device has both a dpap a keyboard, so we report certain keys
      // as dpad, just to avoid having a entry entry in the uni_gamepad_t type.
      switch (usage) {
        case 0x00:  // Reserved, empty on purpose
          break;
        case HID_USAGE_KB_RIGHT_ARROW:
          if (value)
            gamepad->dpad |= DPAD_RIGHT;
          else
            gamepad->dpad &= ~DPAD_RIGHT;
          gamepad->updated_states |= GAMEPAD_STATE_DPAD;
          break;
        case HID_USAGE_KB_LEFT_ARROW:
          if (value)
            gamepad->dpad |= DPAD_LEFT;
          else
            gamepad->dpad &= ~DPAD_LEFT;
          gamepad->updated_states |= GAMEPAD_STATE_DPAD;
          break;
        case HID_USAGE_KB_DOWN_ARROW:
          if (value)
            gamepad->dpad |= DPAD_DOWN;
          else
            gamepad->dpad &= ~DPAD_DOWN;
          gamepad->updated_states |= GAMEPAD_STATE_DPAD;
          break;
        case HID_USAGE_KB_UP_ARROW:
          if (value)
            gamepad->dpad |= DPAD_UP;
          else
            gamepad->dpad &= ~DPAD_UP;
          gamepad->updated_states |= GAMEPAD_STATE_DPAD;
          break;
        case HID_USAGE_KP_ENTER:
          if (value)
            gamepad->buttons |= BUTTON_A;
          else
            gamepad->buttons &= ~BUTTON_A;
          gamepad->updated_states |= GAMEPAD_STATE_BUTTON_A;
          break;
        case HID_USAGE_KB_POWER:
          break;                        // unmapped apparently
        case HID_USAGE_KB_RESERVED_F1:  // Back button (reserved)
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
    case HID_USAGE_PAGE_CONSUMER: {
      switch (usage) {
        case HID_USAGE_MENU:
          if (value)
            gamepad->misc_buttons |= MISC_BUTTON_SYSTEM;
          else
            gamepad->misc_buttons &= ~MISC_BUTTON_SYSTEM;
          gamepad->updated_states |= GAMEPAD_STATE_MISC_BUTTON_SYSTEM;
          break;
        case HID_USAGE_MEDIA_SELECT_TV:
        case HID_USAGE_FAST_FORWARD:
        case HID_USAGE_REWIND:
        case HID_USAGE_PLAY_PAUSE:
        case HID_USAGE_MUTE:
        case HID_USAGE_VOLUMEN_UP:
        case HID_USAGE_VOLUMEN_DOWN:
        case HID_USAGE_AC_SEARCH:  // mic / search
          break;
        case HID_USAGE_AC_HOME:
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