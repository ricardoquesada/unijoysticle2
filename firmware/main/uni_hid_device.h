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

#ifndef UNI_HID_DEVICE_H
#define UNI_HID_DEVICE_H

#include <stdint.h>

#include "btstack.h"
#include "uni_gamepad.h"

#define MAX_NAME_LEN 240
#define MAX_DESCRIPTOR_LEN 512

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

enum DEVICE_STATE { REMOTE_NAME_REQUEST, REMOTE_NAME_INQUIRED, REMOTE_NAME_FETCHED };
typedef struct uni_hid_device_s {
    bd_addr_t               address;
    hci_con_handle_t        con_handle;
    uint8_t                 page_scan_repetition_mode;
    uint16_t                clock_offset;
    uint32_t                cod;
    uint16_t                vendor_id;
    uint16_t                product_id;
    char                    name[MAX_NAME_LEN];

    // incoming, connected, hid, cod, etc...
    uint32_t                flags;

    // SDP
    uint8_t                 hid_descriptor[MAX_DESCRIPTOR_LEN];
    uint16_t                hid_descriptor_len;

    // Channels
    uint16_t                hid_control_cid;
    uint16_t                hid_interrupt_cid;
    enum DEVICE_STATE       state;

    // gamepad
    uni_gamepad_t               gamepad;
    enum JOYSTICK_PORT      joystick_port;                  // which port does it control, A or B?
    enum CONTROLLER_TYPE    controller_type;                // type of controller: joystick or mouse?
} uni_hid_device_t;

void uni_hid_device_init(void);

uni_hid_device_t* uni_hid_device_create(bd_addr_t address);
uni_hid_device_t* uni_hid_device_get_instance_for_address(bd_addr_t addr);
uni_hid_device_t* uni_hid_device_get_instance_for_cid(uint16_t cid);
uni_hid_device_t* uni_hid_device_get_first_device_with_state(int state);

void uni_hid_device_set_current_device(uni_hid_device_t* device);
uni_hid_device_t* uni_hid_device_get_current_device(void);

void uni_hid_device_try_assign_joystick_port(uni_hid_device_t* device);

void uni_hid_device_remove_entry_with_channel(uint16_t channel);

void uni_hid_device_request_inquire(void);

void uni_hid_device_set_disconnected(uni_hid_device_t* device);

void uni_hid_device_set_cod(uni_hid_device_t* device, uint32_t cod);
uint8_t uni_hid_device_is_cod_supported(uint32_t cod);

void uni_hid_device_set_hid_descriptor(uni_hid_device_t* device, const uint8_t* descriptor, int len);
uint8_t uni_hid_device_has_hid_descriptor(uni_hid_device_t* device);

void uni_hid_device_set_incoming(uni_hid_device_t* device, uint8_t incoming);
uint8_t uni_hid_device_is_incoming(uni_hid_device_t* device);

void uni_hid_device_set_name(uni_hid_device_t* device, const uint8_t* name, int name_len);
uint8_t uni_hid_device_has_name(uni_hid_device_t* device);

void uni_hid_device_set_product_id(uni_hid_device_t* device, uint16_t product_id);
uint16_t uni_hid_device_get_product_id(uni_hid_device_t* device);

void uni_hid_device_set_vendor_id(uni_hid_device_t* device, uint16_t vendor_id);
uint16_t uni_hid_device_get_vendor_id(uni_hid_device_t* device);

void uni_hid_device_print_status(uni_hid_device_t* device);

uint8_t uni_hid_device_is_orphan(uni_hid_device_t* device);

#endif // UNI_HID_DEVICE_H
