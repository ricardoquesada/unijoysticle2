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

#include "hid_usage.h"
#include "uni_debug.h"

void uni_hid_parser_ouya_init(uni_gamepad_t* gamepad) {
  // Reset old state. Each report contains a full-state.
  gamepad->updated_states = 0;
}

void uni_hid_parser_ouya_parse_usage(uni_gamepad_t* gamepad,
                                     hid_globals_t* globals,
                                     uint16_t usage_page,
                                     uint16_t usage,
                                     int32_t value) {
  UNUSED(gamepad);
  UNUSED(globals);
  UNUSED(usage_page);
  UNUSED(usage);
  UNUSED(value);

  switch (usage_page) {
    case HID_USAGE_PAGE_GENERIC_DESKTOP:
      switch (usage) {
        case HID_USAGE_AXIS_X:
          gamepad->axis_x = uni_hid_parser_process_axis(globals, value);
          gamepad->updated_states |= GAMEPAD_STATE_AXIS_X;
          break;
        case HID_USAGE_AXIS_Y:
          gamepad->axis_y = uni_hid_parser_process_axis(globals, value);
          gamepad->updated_states |= GAMEPAD_STATE_AXIS_Y;
          break;
        case HID_USAGE_AXIS_Z:
          gamepad->brake = uni_hid_parser_process_pedal(globals, value);
          gamepad->updated_states |= GAMEPAD_STATE_BRAKE;
          break;
        case HID_USAGE_AXIS_RX:
          gamepad->axis_rx = uni_hid_parser_process_axis(globals, value);
          gamepad->updated_states |= GAMEPAD_STATE_AXIS_RX;
          break;
        case HID_USAGE_AXIS_RY:
          gamepad->axis_ry = uni_hid_parser_process_axis(globals, value);
          gamepad->updated_states |= GAMEPAD_STATE_AXIS_RY;
          break;
        case HID_USAGE_AXIS_RZ:
          gamepad->accelerator = uni_hid_parser_process_pedal(globals, value);
          gamepad->updated_states |= GAMEPAD_STATE_ACCELERATOR;
          break;
        default:
          logi("OUYA: Unsupported usage page=0x%04x, page=0x%04x, value=0x%04x\n", usage_page, usage, value);
          break;
      }
      break;
    case HID_USAGE_PAGE_BUTTON:
      switch (usage) {
        case 1:
          if (value)
            gamepad->buttons |= BUTTON_A;
          else
            gamepad->buttons &= ~BUTTON_A;
          gamepad->updated_states |= GAMEPAD_STATE_BUTTON_A;
          break;
        case 2:
          if (value)
            gamepad->buttons |= BUTTON_X;
          else
            gamepad->buttons &= ~BUTTON_X;
          gamepad->updated_states |= GAMEPAD_STATE_BUTTON_X;
          break;
        case 3:
          if (value)
            gamepad->buttons |= BUTTON_Y;
          else
            gamepad->buttons &= ~BUTTON_Y;
          gamepad->updated_states |= GAMEPAD_STATE_BUTTON_Y;
          break;
        case 4:
          if (value)
            gamepad->buttons |= BUTTON_B;
          else
            gamepad->buttons &= ~BUTTON_B;
          gamepad->updated_states |= GAMEPAD_STATE_BUTTON_B;
          break;
        case 5:
          if (value)
            gamepad->buttons |= BUTTON_L;
          else
            gamepad->buttons &= ~BUTTON_L;
          gamepad->updated_states |= GAMEPAD_STATE_BUTTON_L;
          break;
        case 6:
          if (value)
            gamepad->buttons |= BUTTON_R;
          else
            gamepad->buttons &= ~BUTTON_R;
          gamepad->updated_states |= GAMEPAD_STATE_BUTTON_R;
          break;
        case 7:
          if (value)
            gamepad->buttons |= BUTTON_THUMB_L;
          else
            gamepad->buttons &= ~BUTTON_THUMB_L;
          gamepad->updated_states |= GAMEPAD_STATE_BUTTON_THUMB_L;
          break;
        case 8:
          if (value)
            gamepad->buttons |= BUTTON_THUMB_R;
          else
            gamepad->buttons &= ~BUTTON_THUMB_R;
          gamepad->updated_states |= GAMEPAD_STATE_BUTTON_THUMB_R;
          break;
        case 9:
          if (value)
            gamepad->dpad |= DPAD_UP;
          else
            gamepad->dpad &= ~DPAD_UP;
          gamepad->updated_states |= GAMEPAD_STATE_DPAD;
          break;
        case 0x0a:
          if (value)
            gamepad->dpad |= DPAD_DOWN;
          else
            gamepad->dpad &= ~DPAD_DOWN;
          gamepad->updated_states |= GAMEPAD_STATE_DPAD;
          break;
        case 0x0b:
          if (value)
            gamepad->dpad |= DPAD_LEFT;
          else
            gamepad->dpad &= ~DPAD_LEFT;
          gamepad->updated_states |= GAMEPAD_STATE_DPAD;
          break;
        case 0x0c:
          if (value)
            gamepad->dpad |= DPAD_RIGHT;
          else
            gamepad->dpad &= ~DPAD_RIGHT;
          gamepad->updated_states |= GAMEPAD_STATE_DPAD;
          break;
        case 0x0f:
          if (value)
            gamepad->misc_buttons |= MISC_BUTTON_SYSTEM;
          else
            gamepad->misc_buttons &= ~MISC_BUTTON_SYSTEM;
          gamepad->updated_states |= GAMEPAD_STATE_MISC_BUTTON_SYSTEM;
          break;
        default:
          logi("OUYA: Unsupported usage page=0x%04x, page=0x%04x, value=0x%04x\n", usage_page, usage, value);
          break;
      }
      break;
    default:
      logi("OUYA: Unsupported usage page=0x%04x, page=0x%04x, value=0x%04x\n", usage_page, usage, value);
      break;
  }
}