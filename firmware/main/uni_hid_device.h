/****************************************************************************
http://retro.moe/unijoysticle2

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

#include <stdbool.h>
#include <stdint.h>

#include "btstack.h"

#include "uni_gamepad.h"
#include "uni_hid_parser.h"

#define MAX_NAME_LEN 240
#define MAX_DESCRIPTOR_LEN 512

enum DEVICE_STATE {
  REMOTE_NAME_REQUEST,
  REMOTE_NAME_INQUIRED,
  REMOTE_NAME_FETCHED
};

typedef struct uni_hid_device_s {
  bd_addr_t address;
  hci_con_handle_t con_handle;
  uint8_t page_scan_repetition_mode;
  uint16_t clock_offset;
  uint32_t cod;
  uint16_t vendor_id;
  uint16_t product_id;
  char name[MAX_NAME_LEN];

  // incoming, connected, hid, cod, etc...
  uint32_t flags;

  // SDP
  uint8_t hid_descriptor[MAX_DESCRIPTOR_LEN];
  uint16_t hid_descriptor_len;

  // Channels
  uint16_t hid_control_cid;
  uint16_t hid_interrupt_cid;
  enum DEVICE_STATE state;

  // Gamepad
  uni_emulation_mode_t emu_mode;      // type of controller to emulate
  uni_joystick_port_t joystick_port;  // which port does it control, A or B?
  uni_joystick_port_t
      prev_joystick_port;  // which port was used before switching emu mode

  // Functions used to parse the usage page/usage.
  uni_report_parser_t report_parser;

  uni_gamepad_t gamepad;

  // Buttons that needs to be released before triggering the action again.
  uint32_t wait_release_misc_button;

} uni_hid_device_t;

void uni_hid_device_init(void);

uni_hid_device_t* uni_hid_device_create(bd_addr_t address);
uni_hid_device_t* uni_hid_device_get_instance_for_address(bd_addr_t addr);
uni_hid_device_t* uni_hid_device_get_instance_for_cid(uint16_t cid);
uni_hid_device_t* uni_hid_device_get_instance_for_connection_handle(
    hci_con_handle_t handle);
uni_hid_device_t* uni_hid_device_get_first_device_with_state(
    enum DEVICE_STATE state);

void uni_hid_device_set_current_device(uni_hid_device_t* d);
uni_hid_device_t* uni_hid_device_get_current_device(void);

void uni_hid_device_try_assign_joystick_port(uni_hid_device_t* d);

void uni_hid_device_remove_entry_with_channel(uint16_t channel);

void uni_hid_device_request_inquire(void);

void uni_hid_device_set_connected(uni_hid_device_t* d, bool connected);

void uni_hid_device_set_cod(uni_hid_device_t* d, uint32_t cod);
bool uni_hid_device_is_cod_supported(uint32_t cod);

void uni_hid_device_set_hid_descriptor(uni_hid_device_t* d,
                                       const uint8_t* descriptor, int len);
bool uni_hid_device_has_hid_descriptor(uni_hid_device_t* d);

void uni_hid_device_set_incoming(uni_hid_device_t* d, bool incoming);
bool uni_hid_device_is_incoming(uni_hid_device_t* d);

void uni_hid_device_set_name(uni_hid_device_t* d, const uint8_t* name,
                             int name_len);
bool uni_hid_device_has_name(uni_hid_device_t* d);

void uni_hid_device_set_product_id(uni_hid_device_t* d, uint16_t product_id);
uint16_t uni_hid_device_get_product_id(uni_hid_device_t* d);

void uni_hid_device_set_vendor_id(uni_hid_device_t* d, uint16_t vendor_id);
uint16_t uni_hid_device_get_vendor_id(uni_hid_device_t* d);

void uni_hid_device_dump_device(uni_hid_device_t* d);
void uni_hid_device_dump_all(void);

bool uni_hid_device_is_orphan(uni_hid_device_t* d);

void uni_hid_device_guess_controller_type(uni_hid_device_t* d);
bool uni_hid_device_has_controller_type(uni_hid_device_t* d);

void uni_hid_device_process_gamepad(uni_hid_device_t* d);

void uni_hid_device_set_connection_handle(uni_hid_device_t* d,
                                          hci_con_handle_t handle);

void uni_hid_device_set_state(uni_hid_device_t* d, enum DEVICE_STATE s);

void uni_hid_device_send_report(void* d /* uni_hid_device_t */,
                                const uint8_t* report, uint16_t len);

// events

void uni_hid_device_on_emu_mode_change(void);

#endif  // UNI_HID_DEVICE_H
