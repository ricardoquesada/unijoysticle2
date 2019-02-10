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

#include "uni_hid_device.h"

#include "uni_debug.h"
#include "uni_hid_device_vendors.h"

#define MAX_DEVICES                 8

#define MASK_COD_MAJOR_PERIPHERAL   0x0500   // 0b0000_0101_0000_0000
#define MASK_COD_MAJOR_AUDIO        0x0400   // 0b0000_0100_0000_0000
#define MASK_COD_MINOR_MASK         0x00FC   //             1111_1100
#define MASK_COD_MINOR_POINT_DEVICE 0x0080   //             1000_0000
#define MASK_COD_MINOR_KEYBOARD     0x0040   //             0100_0000
#define MASK_COD_MINOR_GAMEPAD      0x0008   //             0000_1000
#define MASK_COD_MINOR_JOYSTICK     0x0004   //             0000_0100
#define MASK_COD_MINOR_HANDS_FREE   0x0008   //             0000_1000

enum {
    FLAGS_INCOMING = (1 << 0),
    FLAGS_CONNECTED = (1 << 1),

    FLAGS_HAS_COD = (1 << 8),
    FLAGS_HAS_NAME = (1 << 9),
    FLAGS_HAS_HID_DESCRIPTOR = (1 << 10),
    FLAGS_HAS_VENDOR_ID = (1 << 11),
    FLAGS_HAS_PRODUCT_ID = (1 << 12),
};

static uni_hid_device_t devices[MAX_DEVICES];
static uni_hid_device_t* current_device = NULL;
static int device_count = 0;
static const bd_addr_t zero_addr = {0,0,0,0,0,0};
static uint32_t used_joystick_ports = 0;            // bitset

void uni_hid_device_init(void) {
    memset(devices, 0, sizeof(devices));
}

uni_hid_device_t* uni_hid_device_create(bd_addr_t address) {
    for (int j=0; j< MAX_DEVICES; j++){
        if (bd_addr_cmp(devices[j].address, zero_addr) == 0) {
            memcpy(devices[j].address, address, 6);
            return &devices[j];
        }
    }
    return NULL;
}

uni_hid_device_t* uni_hid_device_get_instance_for_address(bd_addr_t addr) {
    for (int j=0; j< MAX_DEVICES; j++) {
        if (bd_addr_cmp(addr, devices[j].address) == 0) {
            return &devices[j];
        }
    }
    return NULL;
}

uni_hid_device_t* uni_hid_device_get_instance_for_cid(uint16_t cid) {
    if (cid == 0)
        return NULL;
    for (int i=0; i<MAX_DEVICES; i++) {
        if (devices[i].hid_interrupt_cid == cid || devices[i].hid_control_cid == cid) {
            return &devices[i];
        }
    }
    return NULL;
}

uni_hid_device_t* uni_hid_device_get_first_device_with_state(int state) {
    for (int i=0;i<device_count;i++) {
        if (devices[i].state == state)
            return &devices[i];
    }
    return NULL;
}

void uni_hid_device_set_current_device(uni_hid_device_t* device) {
    current_device = device;
}

uni_hid_device_t* uni_hid_device_get_current_device(void) {
    return current_device;
}

void uni_hid_device_try_assign_joystick_port(uni_hid_device_t* device) {
    if (device == NULL) { log_error("ERROR: Invalid device\n"); return; }

    // All ports already assigned?
    if (used_joystick_ports == JOYSTICK_PORT_AB)
        return;

    // Port already assigned. Do nothing
    if (device->joystick_port != JOYSTICK_PORT_NONE)
        return;

    // Try with Port B, assume it is a joystick
    int wanted_port = JOYSTICK_PORT_B;
    device->controller_emu = EMULATION_MODE_JOYSTICK;

    // ... unless it is a mouse which should try with PORT A. Amiga/Atari ST use mice in PORT A.
    // Undefined on the C64, but most apps use it in PORT A as well.
    uint32_t mouse_cod = MASK_COD_MAJOR_PERIPHERAL | MASK_COD_MINOR_POINT_DEVICE;
    if ((device->cod & mouse_cod) == mouse_cod) {
        wanted_port = JOYSTICK_PORT_A;
        device->controller_emu = EMULATION_MODE_MOUSE;
    }

    // If wanted port is already assigned, try with the next one
    if (used_joystick_ports & wanted_port) {
        logi("Port already assigned, trying another one\n");
        wanted_port = (~wanted_port) & JOYSTICK_PORT_AB;
    }

    used_joystick_ports |= wanted_port;
    device->joystick_port = wanted_port;
    logi("Assigned joystick port: %d\n", wanted_port);
    return;
}

void uni_hid_device_remove_entry_with_channel(uint16_t channel) {
    if (channel == 0)
        return;
    for (int i=0; i<MAX_DEVICES; i++) {
        if (devices[i].hid_control_cid == channel || devices[i].hid_interrupt_cid == channel) {
            memset(&devices[i], 0, sizeof(devices[i]));
            break;
        }
    }
}

void uni_hid_device_request_inquire(void) {
    for (int i=0;i<MAX_DEVICES;i++) {
        // retry remote name request
        if (devices[i].state == REMOTE_NAME_INQUIRED) {
            devices[i].state = REMOTE_NAME_REQUEST;
        }
    }
}

void uni_hid_device_set_disconnected(uni_hid_device_t* device) {
    if (device == NULL) { log_error("ERROR: Invalid device\n"); return; }

    // Connection oriented
    device->flags &= ~(FLAGS_CONNECTED | FLAGS_INCOMING);
    device->hid_control_cid = 0;
    device->hid_interrupt_cid = 0;

    // Joystick-state oriented
    used_joystick_ports &= ~device->joystick_port;
    device->joystick_port = JOYSTICK_PORT_NONE;
}

void uni_hid_device_set_cod(uni_hid_device_t* device, uint32_t cod) {
    if (device == NULL) { log_error("ERROR: Invalid device\n"); return; }

    device->cod = cod;
    if (cod == 0)
        device->flags &= ~FLAGS_HAS_COD;
    else
        device->flags |= FLAGS_HAS_COD;
}

uint8_t uni_hid_device_is_cod_supported(uint32_t cod) {
    const uint32_t minor_cod = cod & MASK_COD_MINOR_MASK;
    // Joysticks, mice, gamepads are valid.
    if ((cod & MASK_COD_MAJOR_PERIPHERAL) == MASK_COD_MAJOR_PERIPHERAL) {
        // device is a peripheral: keyboard, mouse, joystick, gamepad...
        // but we only care about joysticks and gamepads
        return !!(minor_cod & (MASK_COD_MINOR_GAMEPAD
            | MASK_COD_MINOR_JOYSTICK
            | MASK_COD_MINOR_POINT_DEVICE
            | MASK_COD_MINOR_KEYBOARD));
    }

    // For Amazon Fire TV remote contorl: CoD: 0x00400408 (Audio + Telephony : Hands free)
    if ((cod & MASK_COD_MAJOR_AUDIO) == MASK_COD_MAJOR_AUDIO) {
        return !!(minor_cod & MASK_COD_MINOR_HANDS_FREE);
    }
    return 0;
}

void uni_hid_device_set_incoming(uni_hid_device_t* device, uint8_t incoming) {
    if (device == NULL) { log_error("ERROR: Invalid device\n"); return; }

    if (incoming)
        device->flags |= FLAGS_INCOMING;
    else
        device->flags &= ~FLAGS_INCOMING;
}

uint8_t uni_hid_device_is_incoming(uni_hid_device_t* device) {
    return !!(device->flags & FLAGS_INCOMING);
}

void uni_hid_device_set_name(uni_hid_device_t* device, const uint8_t* name, int name_len) {
    if (device == NULL) { log_error("ERROR: Invalid device\n"); return; }
    if (name == NULL) { log_error("Invalid name"); return; }

    if (name != NULL) {
        int min = btstack_min(MAX_NAME_LEN-1, name_len);
        memcpy(device->name, name, min);
        device->name[min] = 0;

        device->flags |= FLAGS_HAS_NAME;
    }
}

uint8_t uni_hid_device_has_name(uni_hid_device_t* device) {
    if (device == NULL) { log_error("ERROR: Invalid device\n"); return 0; }

    return !!(device->flags & FLAGS_HAS_NAME);
}

void uni_hid_device_set_hid_descriptor(uni_hid_device_t* device, const uint8_t* descriptor, int len) {
    if (device == NULL) { log_error("ERROR: Invalid device\n"); return; }

    int min = btstack_min(MAX_DESCRIPTOR_LEN, len);
    memcpy(device->hid_descriptor, descriptor, len);
    device->hid_descriptor_len = min;
    device->flags |= FLAGS_HAS_HID_DESCRIPTOR;
}

uint8_t uni_hid_device_has_hid_descriptor(uni_hid_device_t* device) {
    if (device == NULL) { log_error("ERROR: Invalid device\n"); return 0; }

    return !!(device->flags & FLAGS_HAS_HID_DESCRIPTOR);
}

void uni_hid_device_set_product_id(uni_hid_device_t* device, uint16_t product_id) {
    device->product_id = product_id;
    device->flags |= FLAGS_HAS_PRODUCT_ID;
}

uint16_t uni_hid_device_get_product_id(uni_hid_device_t* device) {
    return device->product_id;
}

void uni_hid_device_set_vendor_id(uni_hid_device_t* device, uint16_t vendor_id) {
    device->vendor_id = vendor_id;
    device->flags |= FLAGS_HAS_VENDOR_ID;
}

uint16_t uni_hid_device_get_vendor_id(uni_hid_device_t* device) {
    return device->vendor_id;
}

void uni_hid_device_print_status(uni_hid_device_t* device) {
    logi("%s: flags=0x%04x, control=%d, interrupt=%d\n",
        bd_addr_to_str(device->address),
        device->flags,
        device->hid_control_cid,
        device->hid_interrupt_cid);
}

uint8_t uni_hid_device_is_orphan(uni_hid_device_t* device) {
    // There is a case with the Apple mouse, and possibly other devices, sends
    // the on_hci_connection_request but doesn't complete the conneciton.
    // The device gets added into the DB at on_hci_connection_request time, and
    // if you later put the device in discovery mode, we won't start a Connection
    // because it is already added to the DB.
    // This prevents that scenario.
    return (device->flags == FLAGS_HAS_COD);
}