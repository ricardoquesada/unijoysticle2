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

#ifndef MY_HID_DEVICE_H
#define MY_HID_DEVICE_H

#include <stdint.h>

#include "btstack.h"

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

enum JOYSTICK_PORT {
    JOYSTICK_PORT_NONE  = 0,
    JOYSTICK_PORT_A     = (1 << 0),
    JOYSTICK_PORT_B     = (1 << 1),
    JOYSTICK_PORT_AB    = (JOYSTICK_PORT_A | JOYSTICK_PORT_B),
};

enum CONTROLLER_TYPE {
    CONTROLLER_JOYSTICK,
    CONTROLLER_MOUSE,
    CONTROLLER_DOUBLE_JOYSTICK,
    CONTROLLER_JOYSTICK_MOUSE,
};

#define MAX_NAME_LEN 240
#define MAX_DESCRIPTOR_LEN 512
typedef struct gamepad {
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
} gamepad_t;

enum DEVICE_STATE { REMOTE_NAME_REQUEST, REMOTE_NAME_INQUIRED, REMOTE_NAME_FETCHED };
typedef struct  {
    bd_addr_t               address;
    hci_con_handle_t        con_handle;
    uint8_t                 page_scan_repetition_mode;
    uint16_t                clock_offset;
    uint32_t                cod;
    char                    name[MAX_NAME_LEN];

    uint32_t                flags;

    // SDP
    uint8_t                 hid_descriptor[MAX_DESCRIPTOR_LEN];
    uint16_t                hid_descriptor_len;

    // Channels
    uint16_t                hid_control_cid;
    uint16_t                hid_interrupt_cid;
    uint16_t                expected_hid_control_psm;         // must be PSM_HID_CONTROL
    uint16_t                expected_hid_interrupt_psm;       // must be PSM_HID_INTERRUPT
    enum DEVICE_STATE       state;

    // gamepad
    gamepad_t               gamepad;
    enum JOYSTICK_PORT      joystick_port;                  // which port does it control, A or B?
    enum CONTROLLER_TYPE    controller_type;                // type of controller: joystick or mouse?
} my_hid_device_t;

void my_hid_device_init(void);

my_hid_device_t* my_hid_device_create(bd_addr_t address);
my_hid_device_t* my_hid_device_get_instance_for_address(bd_addr_t addr);
my_hid_device_t* my_hid_device_get_instance_for_cid(uint16_t cid);
my_hid_device_t* my_hid_device_get_first_device_with_state(int state);

void my_hid_device_set_current_device(my_hid_device_t* device);
my_hid_device_t* my_hid_device_get_current_device(void);

void my_hid_device_try_assign_joystick_port(my_hid_device_t* device);

void my_hid_device_remove_entry_with_channel(uint16_t channel);

void my_hid_device_request_inquire(void);

void my_hid_device_set_disconnected(my_hid_device_t* device);

void my_hid_device_set_cod(my_hid_device_t* device, uint32_t cod);
uint8_t my_hid_device_is_cod_supported(uint32_t cod);

void my_hid_device_set_hid_descriptor(my_hid_device_t* device, const uint8_t* descriptor, int len);
uint8_t my_hid_device_has_hid_descriptor(my_hid_device_t* device);

void my_hid_device_set_incoming(my_hid_device_t* device, uint8_t incoming);
uint8_t my_hid_device_is_incoming(my_hid_device_t* device);

void my_hid_device_set_name(my_hid_device_t* device, const uint8_t* name, int name_len);
uint8_t my_hid_device_has_name(my_hid_device_t* device);

#endif // MY_HID_DEVICE_H
