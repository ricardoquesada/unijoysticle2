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

#include "hid_parser.h"

#include "uni_debug.h"
#include "my_hid_device.h"
#include "gpio_joy.h"

enum {
    DPAD_UP     = 1 << 0,
    DPAD_DOWN   = 1 << 1,
    DPAD_RIGHT  = 1 << 2,
    DPAD_LEFT   = 1 << 3,
};

enum {
    MISC_AC_SEARCH  = 1 << 0,
    MISC_AC_HOME    = 1 << 1,
    MISC_AC_BACK    = 1 << 2,

    MISC_SYS_MAIN_MENU = 1 << 3,
};

// btstack bug:
// see: https://github.com/bluekitchen/btstack/issues/187
typedef struct {
    int32_t         logical_minimum;
    int32_t         logical_maximum;
    uint16_t        usage_page;
    uint8_t         report_size;
    uint8_t         report_count;
    uint8_t         report_id;
} hid_globals_t;

static const int AXIS_NORMALIZE_RANGE = 1024;  // 10-bit resolution (1024)
static const int AXIS_THRESHOLD = 1024 / 4;

static int32_t hid_process_axis(btstack_hid_parser_t* parser, hid_globals_t* globals, uint32_t value);
static uint8_t hid_process_hat(btstack_hid_parser_t* parser, hid_globals_t* globals, uint32_t value);
static void joystick_update(my_hid_device_t* device);
static void process_usage(my_hid_device_t* device, btstack_hid_parser_t* parser, hid_globals_t* globals, uint16_t usage_page, uint16_t usage, int32_t value);
static void print_gamepad(gamepad_t* gamepad);

void hid_parser_handle_interrupt_report(my_hid_device_t* device, const uint8_t * report, uint16_t report_len) {
    btstack_hid_parser_t parser;

    // check if HID Input Report
    if (report_len < 1) return;
    if (*report != 0xa1) return;
    report++;
    report_len--;

    if (!my_hid_device_has_hid_descriptor(device)) {
        logi("Device without HID descriptor yet. Ignoring report\n");
        return;
    }

    // In case a joystick port hasn't been assign yet, assign one.
    my_hid_device_try_assign_joystick_port(device);

    btstack_hid_parser_init(&parser, device->hid_descriptor, device->hid_descriptor_len, HID_REPORT_TYPE_INPUT, report, report_len);
    device->gamepad.updated_states = 0;
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
        process_usage(device, &parser, &globals, usage_page, usage, value);
    }
    // Debug info
    print_gamepad(&device->gamepad);

    joystick_update(device);
}

static void process_usage(my_hid_device_t* device, btstack_hid_parser_t* parser, hid_globals_t* globals, uint16_t usage_page, uint16_t usage, int32_t value) {
    // print_parser_globals(globals);
    switch (usage_page) {
    case 0x01:  // Generic Desktop controls
        switch (usage) {
        case 0x30:  // x
            device->gamepad.x = hid_process_axis(parser, globals, value);
            device->gamepad.updated_states |= GAMEPAD_STATE_X;
            break;
        case 0x31:  // y
            device->gamepad.y = hid_process_axis(parser, globals, value);
            device->gamepad.updated_states |= GAMEPAD_STATE_Y;
            break;
        case 0x32:  // z
            device->gamepad.z = hid_process_axis(parser, globals, value);
            device->gamepad.updated_states |= GAMEPAD_STATE_Z;
            break;
        case 0x33:  // rx
            device->gamepad.rx = hid_process_axis(parser, globals, value);
            device->gamepad.updated_states |= GAMEPAD_STATE_RX;
            break;
        case 0x34:  // ry
            device->gamepad.ry = hid_process_axis(parser, globals, value);
            device->gamepad.updated_states |= GAMEPAD_STATE_RY;
            break;
        case 0x35:  // rz
            device->gamepad.rz = hid_process_axis(parser, globals, value);
            device->gamepad.updated_states |= GAMEPAD_STATE_RZ;
            break;
        case 0x39:  // switch hat
            device->gamepad.hat = hid_process_hat(parser, globals, value);
            device->gamepad.updated_states |= GAMEPAD_STATE_HAT;
            break;
        case 0x85: // system main menu
            if (value)
                device->gamepad.misc_buttons |= MISC_SYS_MAIN_MENU;
            else
                device->gamepad.misc_buttons &= ~MISC_SYS_MAIN_MENU;
            break;
        case 0x90:  // dpad up
            if (value)
                device->gamepad.dpad |= DPAD_UP;
            else
                device->gamepad.dpad &= ~DPAD_UP;
            device->gamepad.updated_states |= GAMEPAD_STATE_DPAD;
            break;
        case 0x91:  // dpad down
            if (value)
                device->gamepad.dpad |= DPAD_DOWN;
            else
                device->gamepad.dpad &= ~DPAD_DOWN;
            device->gamepad.updated_states |= GAMEPAD_STATE_DPAD;
            break;
        case 0x92:  // dpad right
            if (value)
                device->gamepad.dpad |= DPAD_RIGHT;
            else
                device->gamepad.dpad &= ~DPAD_RIGHT;
            device->gamepad.updated_states |= GAMEPAD_STATE_DPAD;
            break;
        case 0x93:  // dpad left
            if (value)
                device->gamepad.dpad |= DPAD_LEFT;
            else
                device->gamepad.dpad &= ~DPAD_LEFT;
            device->gamepad.updated_states |= GAMEPAD_STATE_DPAD;
            break;
        default:
            logi("Unsupported page: 0x%04x, usage: 0x%04x, value=0x%x\n", usage_page, usage, value);
            break;
        }
        break;
    case 0x02:  // Simulation controls
        switch (usage) {
        case 0xc4:  // accelerator
            device->gamepad.accelerator = value;
            device->gamepad.updated_states |= GAMEPAD_STATE_ACCELERATOR;
            break;
        case 0xc5:  // brake
            device->gamepad.brake = value;
            device->gamepad.updated_states |= GAMEPAD_STATE_BRAKE;
            break;
        default:
            logi("Unsupported page: 0x%04x, usage: 0x%04x, value=0x%x\n", usage_page, usage, value);
            break;
        };
        break;
    case 0x06: // Generic Device Controls Page
        switch (usage) {
        case 0x20: // Battery Strength
            device->gamepad.battery = value;
            break;
        default:
            logi("Unsupported page: 0x%04x, usage: 0x%04x, value=0x%x\n", usage_page, usage, value);
            break;
        }
        break;
    case 0x07:  // Keypad / Keyboard
        // FIXME: It is unlikely a device has both a dpap a keyboard, so we report certain keys
        // as dpad, just to avoid having a entry entry in the gamepad_t type.
        switch (usage) {
        case 0x00:  // Reserved
            // empty on purpose
            break;
        case 0x4f:  // Right arrow
        case 0x5e:  // Keypad right arrow
            if (value)
                device->gamepad.dpad |= DPAD_RIGHT;
            else
                device->gamepad.dpad &= ~DPAD_RIGHT;
            device->gamepad.updated_states |= GAMEPAD_STATE_DPAD;
            break;
        case 0x50:  // Left arrow
        case 0x5c:  // Keypad left arrow
            if (value)
                device->gamepad.dpad |= DPAD_LEFT;
            else
                device->gamepad.dpad &= ~DPAD_LEFT;
            device->gamepad.updated_states |= GAMEPAD_STATE_DPAD;
            break;
        case 0x51:  // Down arrow
        case 0x5a:  // Keypad down arrow
            if (value)
                device->gamepad.dpad |= DPAD_DOWN;
            else
                device->gamepad.dpad &= ~DPAD_DOWN;
            device->gamepad.updated_states |= GAMEPAD_STATE_DPAD;
            break;
        case 0x52:  // Up arrow
        case 0x60:  // Keypad up arrow
            if (value)
                device->gamepad.dpad |= DPAD_UP;
            else
                device->gamepad.dpad &= ~DPAD_UP;
            device->gamepad.updated_states |= GAMEPAD_STATE_DPAD;
            break;
        case 0x1d:  // z
        case 0x28:  // Enter
        case 0x2c:  // spacebar
        case 0x58:  // Keypad enter
            if (value)
                device->gamepad.buttons |= (1 << 0);
            else
                device->gamepad.buttons &= ~(1 << 0);
            device->gamepad.updated_states |= GAMEPAD_STATE_BUTTON0;
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
                device->gamepad.buttons |= (1 << button_idx);
            else
                device->gamepad.buttons &= ~(1 << button_idx);
            device->gamepad.updated_states |= (GAMEPAD_STATE_BUTTON0 << button_idx);
        } else {
            logi("Unsupported page: 0x%04x, usage: 0x%04x, value=0x%x\n", usage_page, usage, value);
        }
        break;
    }
    case 0x0c:  // Consumer
        switch (usage) {
        case 0x221:     // search
            if (value)
                device->gamepad.misc_buttons |= MISC_AC_SEARCH;
            else
                device->gamepad.misc_buttons &= ~MISC_AC_SEARCH;
        case 0x0223:    // home
            if (value)
                device->gamepad.misc_buttons |= MISC_AC_HOME;
            else
                device->gamepad.misc_buttons &= ~MISC_AC_HOME;
            break;
        case 0x0224:    // back
            if (value)
                device->gamepad.misc_buttons |= MISC_AC_BACK;
            else
                device->gamepad.misc_buttons &= ~MISC_AC_BACK;
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

static void print_gamepad(gamepad_t* gamepad) {
    logd("(0x%04x) x=%d, y=%d, z=%d, rx=%d, ry=%d, rz=%d, hat=0x%02x, dpad=0x%02x, accel=%d, brake=%d, buttons=0x%08x, misc=0x%02x\n",
        gamepad->updated_states,
        gamepad->x, gamepad->y, gamepad->z,
        gamepad->rx, gamepad->ry, gamepad->rz,
        gamepad->hat,
        gamepad->dpad,
        gamepad->accelerator, gamepad->brake,
        gamepad->buttons,
        gamepad->misc_buttons);
}

// Converts gamepad to joystick.
static void joystick_update(my_hid_device_t* device) {
    if (device->joystick_port == JOYSTICK_PORT_NONE)
        return;

    // FIXME: Add support for JOYSTICK_PORT_AB.
    joystick_t joy;

    // reset state
    memset(&joy, 0, sizeof(joy));

    const gamepad_t* gp = &device->gamepad;
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
    switch(device->controller_type) {
    case CONTROLLER_JOYSTICK:
        if (device->joystick_port == JOYSTICK_PORT_A)
            gpio_joy_update_port_a(&joy);
        else
            gpio_joy_update_port_b(&joy);
        break;
    case CONTROLLER_MOUSE:
        gpio_joy_update_mouse(gp->x, gp->y);
        break;
    default:
        loge("Unsupported controller type: %d\n", device->controller_type);
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
static int32_t hid_process_axis(btstack_hid_parser_t* parser, hid_globals_t* globals, uint32_t value) {
    UNUSED(parser);

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

static uint8_t hid_process_hat(btstack_hid_parser_t* parser, hid_globals_t* globals, uint32_t value) {
    UNUSED(parser);
    int32_t v = (int32_t) value;
    // Assumes if value is outside valid range, then it is a "null value"
    if (v < globals->logical_minimum || v > globals->logical_maximum)
        return 0xff;
    // 0 should be the first value for hat, meaning that 0 is the "up" position.
    return v - globals->logical_minimum;
}
