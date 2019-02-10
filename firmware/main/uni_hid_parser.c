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

#include "uni_hid_parser.h"

#include "uni_debug.h"
#include "uni_hid_device.h"
#include "uni_hid_parser_generic.h"
#include "uni_gamepad.h"
#include "gpio_joy.h"

static const int AXIS_NORMALIZE_RANGE = 1024;  // 10-bit resolution (1024)
static const int AXIS_THRESHOLD = 1024 / 4;

uni_gamepad_t uni_hid_parser(const uint8_t* report, uint16_t report_len, const uint8_t* hid_descriptor, uint16_t hid_descriptor_len) {
    btstack_hid_parser_t parser;
    uni_gamepad_t gamepad;

    memset(&gamepad, 0, sizeof(gamepad));
    btstack_hid_parser_init(&parser, hid_descriptor, hid_descriptor_len, HID_REPORT_TYPE_INPUT, report, report_len);
    gamepad.updated_states = 0;
    while (btstack_hid_parser_has_more(&parser)){
        uint16_t usage_page;
        uint16_t usage;
        int32_t  value;
        hid_globals_t globals;

        // Save globals, otherwise they are going to get destroyed by btstack_hid_parser_get_field()
        globals.logical_minimum = parser.global_logical_minimum;
        globals.logical_maximum = parser.global_logical_maximum;
        globals.report_count = parser.global_report_count;
        globals.report_id = parser.global_report_id;
        globals.report_size = parser.global_report_size;
        globals.usage_page = parser.global_usage_page;

        btstack_hid_parser_get_field(&parser, &usage_page, &usage, &value);

        logd("usage_page = 0x%04x, usage = 0x%04x, value = 0x%x - ", usage_page, usage, value);
        uni_hid_parser_generic(&gamepad, &globals, usage_page, usage, value);
    }
    return gamepad;
}

// Converts gamepad to joystick.
// FIXME: should be placed somewhere else.
void joystick_update(const uni_gamepad_t* gp, uni_joystick_port_t joy_port, uni_controller_type_t ctl_type) {
    if (joy_port == JOYSTICK_PORT_NONE)
        return;

    // FIXME: Add support for JOYSTICK_PORT_AB.
    joystick_t joy;

    // reset state
    memset(&joy, 0, sizeof(joy));

    if (gp->updated_states & GAMEPAD_STATE_HAT) {
        switch (gp->hat) {
        case 0xff:
            // joy.up = joy.down = joy.left = joy.right = 0;
            break;
        case 0:
            joy.up |= 1;
            break;
        case 1:
            joy.up |= 1;
            joy.right |= 1;
            break;
        case 2:
            joy.right |= 1;
            break;
        case 3:
            joy.right |= 1;
            joy.down |= 1;
            break;
        case 4:
            joy.down |= 1;
            break;
        case 5:
            joy.down |= 1;
            joy.left |= 1;
            break;
        case 6:
            joy.left |= 1;
            break;
        case 7:
            joy.left |= 1;
            joy.up |= 1;
            break;
        default:
            loge("Error parsing hat values\n");
            break;
        }
    }

    if (gp->updated_states & GAMEPAD_STATE_DPAD) {
        if (gp->dpad & 0x01)
            joy.up |= 1;
        if (gp->dpad & 0x02)
            joy.down |= 1;
        if (gp->dpad & 0x04)
            joy.right |= 1;
        if (gp->dpad & 0x08)
            joy.left |= 1;
    }

    // Button A is "fire"
    if (gp->updated_states & GAMEPAD_STATE_BUTTON0) {
        joy.fire |= gp->buttons & 0x1;
    }

    // Button B is "jump"
    if (gp->updated_states & GAMEPAD_STATE_BUTTON1) {
        joy.up |= ((gp->buttons & 0x2) == 0x2);
    }

    // Axis: x and y
    if (gp->updated_states & GAMEPAD_STATE_X) {
        joy.left |= (gp->x < -AXIS_THRESHOLD);
        joy.right |= (gp->x > AXIS_THRESHOLD);
    }
    if (gp->updated_states & GAMEPAD_STATE_Y) {
        joy.up |= (gp->y < -AXIS_THRESHOLD);
        joy.down |= (gp->y > AXIS_THRESHOLD);
    }

    // FIXME: Add support for JOYSTICK_PORT_AB.
    switch(ctl_type) {
    case CONTROLLER_JOYSTICK:
        if (joy_port == JOYSTICK_PORT_A)
            gpio_joy_update_port_a(&joy);
        else
            gpio_joy_update_port_b(&joy);
        break;
    case CONTROLLER_MOUSE:
        gpio_joy_update_mouse(gp->x, gp->y);
        break;
    default:
        loge("Unsupported controller type: %d\n", ctl_type);
        break;
    }
}

// static uint32_t next_pot(uint32_t n) {
//     n--;
//     n |= n >> 1;
//     n |= n >> 2;
//     n |= n >> 4;
//     n |= n >> 8;
//     n |= n >> 16;
//     return n + 1;    
// }

// Converts a possible value between (0, x) to (-x/2, x/2), and normalizes it between -512 and 511.
int32_t uni_hid_process_axis(hid_globals_t* globals, uint32_t value) {
    int32_t max = globals->logical_maximum;
    int32_t min = globals->logical_minimum;

    // Amazon Fire 1st Gen reports max value as unsigned (0xff == 255) but the spec says they are signed.
    // So the parser correctly treats it as -1 (0xff).
    if (max == -1) {
        max = (1 << globals->report_size) - 1;
    }

    // Get the range: how big can be the number
    int32_t range = max - min;
    // range = next_pot(range);

    // First we "center" the value, meaning that 0 is when the axis is not used.
    int32_t centered = value - range / 2 - min;

    // Then we normalize between -512 and 511
    int32_t normalized = centered * AXIS_NORMALIZE_RANGE / range;
    logd("original = %d, centered = %d, normalized = %d (range = %d, min=%d, max=%d)\n", value, centered, normalized, range, min, max);

    return normalized;
}

uint8_t uni_hid_process_hat(hid_globals_t* globals, uint32_t value) {
    int32_t v = (int32_t) value;
    // Assumes if value is outside valid range, then it is a "null value"
    if (v < globals->logical_minimum || v > globals->logical_maximum)
        return 0xff;
    // 0 should be the first value for hat, meaning that 0 is the "up" position.
    return v - globals->logical_minimum;
}
