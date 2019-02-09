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

enum GAMEPAD_STATES {
    GAMEPAD_STATE_HAT = 1 << 0,
    GAMEPAD_STATE_X = 1 << 1,
    GAMEPAD_STATE_Y = 1 << 2,
    GAMEPAD_STATE_Z = 1 << 3,
    GAMEPAD_STATE_RX = 1 << 4,
    GAMEPAD_STATE_RY = 1 << 5,
    GAMEPAD_STATE_RZ = 1 << 6,
    GAMEPAD_STATE_DPAD = 1 << 7,
    GAMEPAD_STATE_BRAKE = 1 << 8,
    GAMEPAD_STATE_ACCELERATOR = 1 << 9,
    GAMEPAD_STATE_BUTTON0 = 1 << 10,
    GAMEPAD_STATE_BUTTON1 = 1 << 11,
    GAMEPAD_STATE_BUTTON2 = 1 << 12,
    GAMEPAD_STATE_BUTTON3 = 1 << 13,
    GAMEPAD_STATE_BUTTON4 = 1 << 14,
    GAMEPAD_STATE_BUTTON5 = 1 << 15,
    GAMEPAD_STATE_BUTTON6 = 1 << 16,
    GAMEPAD_STATE_BUTTON7 = 1 << 17,
    GAMEPAD_STATE_BUTTON8 = 1 << 18,
    GAMEPAD_STATE_BUTTON9 = 1 << 19,
    GAMEPAD_STATE_BUTTON10 = 1 << 20,
    GAMEPAD_STATE_BUTTON11 = 1 << 21,
    GAMEPAD_STATE_BUTTON12 = 1 << 22,
    GAMEPAD_STATE_BUTTON13 = 1 << 23,
    GAMEPAD_STATE_BUTTON14 = 1 << 24,
    GAMEPAD_STATE_BUTTON15 = 1 << 25,
};

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

typedef struct {
    // Usage Page: 0x01 (Generic Desktop Controls)
    uint8_t hat;
    int32_t x;
    int32_t y;
    int32_t z;
    int32_t rx;
    int32_t ry;
    int32_t rz;
    uint8_t dpad;

    // Usage Page: 0x02 (Sim controls)
    int32_t     brake;
    int32_t     accelerator;

    // Usage Page: 0x06 (Generic dev controls)
    uint16_t    battery;

    // Usage Page: 0x09 (Button)
    uint32_t    buttons;

    // Misc buttos (from 0x0c (Consumer) and others)
    uint8_t     misc_buttons;

    // updated states
    uint32_t    updated_states;
} uni_gamepad_t;


void uni_gamepad_dump(uni_gamepad_t* gamepad);
#endif // UNI_GAMEPAD_H