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

#ifndef UNI_GAMEPAD_H
#define UNI_GAMEPAD_H

#include <stdint.h>

// FIXME: doesn't seem to belong in this file.
typedef enum {
    JOYSTICK_PORT_NONE  = 0,
    JOYSTICK_PORT_A     = (1 << 0),
    JOYSTICK_PORT_B     = (1 << 1),
    JOYSTICK_PORT_AB    = (JOYSTICK_PORT_A | JOYSTICK_PORT_B),
} uni_joystick_port_t;

// FIXME: doesn't seem to belong in this file.
typedef enum {
    EMULATION_MODE_JOYSTICK,
    EMULATION_MODE_MOUSE,
    EMULATION_MODE_COMBO_JOY_MOUSE,
    EMULATION_MODE_COMBO_JOY_JOY
} uni_emulation_mode_t;

enum {
    DPAD_UP     = 1 << 0,
    DPAD_DOWN   = 1 << 1,
    DPAD_RIGHT  = 1 << 2,
    DPAD_LEFT   = 1 << 3,
};

enum {
    BUTTON_A    = 1 << 0,
    BUTTON_B    = 1 << 1,
    BUTTON_C    = 1 << 2,
    BUTTON_X    = 1 << 3,
    BUTTON_Y    = 1 << 4,
    BUTTON_Z    = 1 << 5,
    BUTTON_L    = 1 << 6,
    BUTTON_R    = 1 << 7,
};

enum {
    MISC_AC_HOME    = 1 << 0,
    MISC_AC_SEARCH  = 1 << 1,
    MISC_AC_BACK    = 1 << 2,
    MISC_SYS_MAIN_MENU = 1 << 3,
};

enum {
    GAMEPAD_STATE_DPAD = 1 << 0,
    
    GAMEPAD_STATE_AXIS_X = 1 << 1,
    GAMEPAD_STATE_AXIS_Y = 1 << 2,
    GAMEPAD_STATE_AXIS_RX = 1 << 3,
    GAMEPAD_STATE_AXIS_RY = 1 << 4,
    
    GAMEPAD_STATE_BRAKE = 1 << 5,
    GAMEPAD_STATE_ACCELERATOR = 1 << 6,

    GAMEPAD_STATE_BUTTON_A = 1 << 10,
    GAMEPAD_STATE_BUTTON_B = 1 << 11,
    GAMEPAD_STATE_BUTTON_C = 1 << 12,
    GAMEPAD_STATE_BUTTON_X = 1 << 13,
    GAMEPAD_STATE_BUTTON_Y = 1 << 14,
    GAMEPAD_STATE_BUTTON_Z = 1 << 15,
    GAMEPAD_STATE_BUTTON_L = 1 << 16,
    GAMEPAD_STATE_BUTTON_R = 1 << 17,

    GAMEPAD_STATE_BUTTON_MISC_HOME = 1 << 20,
    GAMEPAD_STATE_BUTTON_MISC_SEARCH = 1 << 21,
    GAMEPAD_STATE_BUTTON_MISC_BACK = 1 << 22,
    GAMEPAD_STATE_BUTTON_MISC_MAIN_MENU = 1 << 23,
};

// uni_gamepad_t is a virtual gamepad.
// Different parsers should populate this virtual gamepad accordingly.
// For example, the virtual gamepad doesn't have a Hat, but has a D-pad.
// If the real gamepad has a Hat, it should populate the D-pad instead.
//
// If the real device only has one joy-pad, it should populate the left side
// of the virtual gamepad.
// Example: a TV remote control should populate the left d-pad and the left
// joypad.
//
// The virtual gamepad will then be processed by the dfferent retro-computer
// joysticks.
//
// Virtual Gamepad layout:
//
//
//  Left             Center            Right
//
//  brake: 0-1023    Menu button       accelerator: 0-1023
//  L-button                           R-button
//  d-pad                              buttons: A,B,C,X,Y,Z
//  l-joypad (axis: -512, 511)         r-joypad (axis: -512, 511)
typedef struct {
    // Usage Page: 0x01 (Generic Desktop Controls)
    uint8_t     dpad;
    int32_t     axis_x;
    int32_t     axis_y;
    int32_t     axis_rx;
    int32_t     axis_ry;

    // Usage Page: 0x02 (Sim controls)
    int32_t     brake;
    int32_t     accelerator;

    // Usage Page: 0x06 (Generic dev controls)
    uint16_t    battery;

    // Usage Page: 0x09 (Button)
    uint16_t    buttons;

    // Misc buttos (from 0x0c (Consumer) and others)
    uint8_t     misc_buttons;

    // updated states
    uint32_t    updated_states;
} uni_gamepad_t;


void uni_gamepad_dump(uni_gamepad_t* gamepad);
#endif // UNI_GAMEPAD_H