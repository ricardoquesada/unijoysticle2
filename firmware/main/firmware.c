/*
 * Copyright (C) 2017 BlueKitchen GmbH
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holders nor the names of
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 * 4. Any redistribution, use, or modification is done solely for
 *    personal benefit and not for any commercial purpose or for
 *    monetary gain.
 *
 * THIS SOFTWARE IS PROVIDED BY BLUEKITCHEN GMBH AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL MATTHIAS
 * RINGWALD OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
 * THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * Please inquire about commercial licensing options at
 * contact@bluekitchen-gmbh.com
 *
 */

/*
 * Copyright (C) 2019 Ricardo Quesada
 * Unijoysticle additions based on the following BlueKitchen's test/example files:
 *   - hid_host_test.c
 *   - hid_device.c
 *   - gap_inquire.c
 *   - hid_device_test.c
 *   - gap_link_keys.c
 */

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "btstack_config.h"
#include "btstack.h"

#include "gpio_joy.h"
#include "uni_hid_parser.h"
#include "uni_hid_device.h"
#include "uni_debug.h"

#define INQUIRY_INTERVAL            5
#define MAX_ATTRIBUTE_VALUE_SIZE    512      // Apparently PS4 has a 470-bytes report
#define MTU                         100

// globals
// SDP
static uint8_t            attribute_value[MAX_ATTRIBUTE_VALUE_SIZE];
static const unsigned int attribute_value_buffer_size = MAX_ATTRIBUTE_VALUE_SIZE;

static btstack_packet_callback_registration_t hci_event_callback_registration;

static void packet_handler(uint8_t packet_type, uint16_t channel, uint8_t *packet, uint16_t size);
static void handle_sdp_hid_query_result(uint8_t packet_type, uint16_t channel, uint8_t *packet, uint16_t size);
static void handle_sdp_did_query_result(uint8_t packet_type, uint16_t channel, uint8_t *packet, uint16_t size);
static void continue_remote_names(void);
static void start_scan(void);
static void sdp_query_hid_descriptor(uni_hid_device_t* device);
static void sdp_query_product_id(uni_hid_device_t* device);
static void list_link_keys(void);

static void on_l2cap_channel_closed(uint8_t* packet, uint16_t channel);
static void on_l2cap_channel_opened(uint8_t* packet, uint16_t channel);
static void on_l2cap_incoming_connection(uint8_t *packet, uint16_t channel);
static void on_gap_inquiry_result(uint8_t* packet, uint16_t channel);
static void on_hci_connection_request(uint8_t* packet, uint16_t channel);

int btstack_main(int argc, const char * argv[]);

static void hid_host_setup(void){

    // enabled EIR
    hci_set_inquiry_mode(INQUIRY_MODE_RSSI_AND_EIR);

    // register for HCI events
    hci_event_callback_registration.callback = &packet_handler;
    hci_add_event_handler(&hci_event_callback_registration);

    l2cap_register_service(packet_handler, PSM_HID_INTERRUPT, MTU, LEVEL_2);
    l2cap_register_service(packet_handler, PSM_HID_CONTROL,   MTU, LEVEL_2);

    // Disable stdout buffering
    setbuf(stdout, NULL);
}

// HID results: HID descriptor, PSM interrupt, PSM control, etc.
static void handle_sdp_hid_query_result(uint8_t packet_type, uint16_t channel, uint8_t *packet, uint16_t size) {

    UNUSED(packet_type);
    UNUSED(channel);
    UNUSED(size);

    des_iterator_t  attribute_list_it;
    des_iterator_t  additional_des_it;
    uint8_t*        des_element;
    uint8_t*        element;
    uni_hid_device_t* device;

    device = uni_hid_device_get_current_device();
    if (device == NULL) {
        loge("ERROR: handle_sdp_client_query_result. current device = NULL\n");
        return;
    }

    switch (hci_event_packet_get_type(packet)){
    case SDP_EVENT_QUERY_ATTRIBUTE_VALUE:
        if (sdp_event_query_attribute_byte_get_attribute_length(packet) <= attribute_value_buffer_size) {
            attribute_value[sdp_event_query_attribute_byte_get_data_offset(packet)] = sdp_event_query_attribute_byte_get_data(packet);
            if ((uint16_t)(sdp_event_query_attribute_byte_get_data_offset(packet)+1) == sdp_event_query_attribute_byte_get_attribute_length(packet)) {
                switch(sdp_event_query_attribute_byte_get_attribute_id(packet)) {
                case BLUETOOTH_ATTRIBUTE_HID_DESCRIPTOR_LIST:
                    for (des_iterator_init(&attribute_list_it, attribute_value); des_iterator_has_more(&attribute_list_it); des_iterator_next(&attribute_list_it)) {
                        if (des_iterator_get_type(&attribute_list_it) != DE_DES) continue;
                        des_element = des_iterator_get_element(&attribute_list_it);
                        for (des_iterator_init(&additional_des_it, des_element); des_iterator_has_more(&additional_des_it); des_iterator_next(&additional_des_it)) {
                            if (des_iterator_get_type(&additional_des_it) != DE_STRING) continue;
                            element = des_iterator_get_element(&additional_des_it);
                            const uint8_t * descriptor = de_get_string(element);
                            int descriptor_len = de_get_data_size(element);
                            logi("SDP HID Descriptor (%d):\n", descriptor_len);
                            uni_hid_device_set_hid_descriptor(device, descriptor, descriptor_len);
                            printf_hexdump(descriptor, descriptor_len);
                        }
                    }
                    break;
                default:
                    break;
                }
            }
        } else {
            loge("SDP attribute value buffer size exceeded: available %d, required %d\n", attribute_value_buffer_size, sdp_event_query_attribute_byte_get_attribute_length(packet));
        }
        break;
    case SDP_EVENT_QUERY_COMPLETE:
        sdp_query_product_id(device);
        break;
    default:
        break;
    }
}

// Device ID results: Vendor ID, Product ID, Version, etc...
static void handle_sdp_did_query_result(uint8_t packet_type, uint16_t channel, uint8_t *packet, uint16_t size) {
    UNUSED(packet_type);
    UNUSED(channel);
    UNUSED(size);

    uni_hid_device_t* device;
    uint16_t        id16;

    device = uni_hid_device_get_current_device();
    if (device == NULL) {
        loge("ERROR: handle_sdp_client_query_result. current device = NULL\n");
        return;
    }

    switch (hci_event_packet_get_type(packet)){
    case SDP_EVENT_QUERY_ATTRIBUTE_VALUE:
        if (sdp_event_query_attribute_byte_get_attribute_length(packet) <= attribute_value_buffer_size) {
            attribute_value[sdp_event_query_attribute_byte_get_data_offset(packet)] = sdp_event_query_attribute_byte_get_data(packet);
            if ((uint16_t)(sdp_event_query_attribute_byte_get_data_offset(packet)+1) == sdp_event_query_attribute_byte_get_attribute_length(packet)) {
                switch(sdp_event_query_attribute_byte_get_attribute_id(packet)) {
                case BLUETOOTH_ATTRIBUTE_VENDOR_ID:
                    if (de_element_get_uint16(attribute_value, &id16))
                        uni_hid_device_set_vendor_id(device, id16);
                    else loge("Error getting vendor id\n");
                    break;

                case BLUETOOTH_ATTRIBUTE_PRODUCT_ID:
                    if (de_element_get_uint16(attribute_value, &id16))
                        uni_hid_device_set_product_id(device, id16);
                    else loge("Error getting product id\n");
                    break;
                default:
                    break;
                }
            }
        } else {
            loge("SDP attribute value buffer size exceeded: available %d, required %d\n", attribute_value_buffer_size, sdp_event_query_attribute_byte_get_attribute_length(packet));
        }
        break;
    case SDP_EVENT_QUERY_COMPLETE:
        logi("Vendor ID: 0x%04x - Product ID: 0x%04x\n", uni_hid_device_get_vendor_id(device), uni_hid_device_get_product_id(device));
        uni_hid_device_set_current_device(NULL);
        break;
    }
}

static void packet_handler(uint8_t packet_type, uint16_t channel, uint8_t *packet, uint16_t size) {
    static uint8_t bt_ready = 0;

    uint8_t   event;
    bd_addr_t event_addr;
    uni_hid_device_t* device;

    // Ignore all packet events if bt is not ready, with the exception of the "bt is ready" event.
    if ((!bt_ready) &&
        !((packet_type == HCI_EVENT_PACKET) && (hci_event_packet_get_type(packet) == BTSTACK_EVENT_STATE))
        ) {
            // printf("Ignoring packet. BT not ready yet\n");
        return;
    }

    switch (packet_type) {
    case HCI_EVENT_PACKET:
        event = hci_event_packet_get_type(packet);
        switch (event) {
        case BTSTACK_EVENT_STATE:
            if (btstack_event_state_get_state(packet) == HCI_STATE_WORKING) {
                bt_ready = 1;
                logi("Btstack ready!\n");
                list_link_keys();
                start_scan();
            }
            break;

        // HCI EVENTS
        case HCI_EVENT_PIN_CODE_REQUEST:
            // inform about pin code request
            logi("Pin code request - using '0000'\n");
            hci_event_pin_code_request_get_bd_addr(packet, event_addr);
            gap_pin_code_response(event_addr, "0000");
            break;
        case HCI_EVENT_USER_CONFIRMATION_REQUEST:
            // inform about user confirmation request
            logi("SSP User Confirmation Request with numeric value '%"PRIu32"'\n", little_endian_read_32(packet, 8));
            logi("SSP User Confirmation Auto accept\n");
            break;
        case HCI_EVENT_HID_META:
            logi("UNSUPPORTED ---> HCI_EVENT_HID_META <---\n");
            break;
        case HCI_EVENT_INQUIRY_RESULT:
            // printf("--> HCI_EVENT_INQUIRY_RESULT <--\n");
            break;
        case HCI_EVENT_CONNECTION_REQUEST:
            logi("--> HCI_EVENT_CONNECTION_REQUEST <--\n");
            on_hci_connection_request(packet, channel);
            break;
        case HCI_EVENT_INQUIRY_RESULT_WITH_RSSI:
            // logi("--> HCI_EVENT_INQUIRY_RESULT_WITH_RSSI <--\n");
            break;
        case HCI_EVENT_EXTENDED_INQUIRY_RESPONSE:
            // logi("--> HCI_EVENT_EXTENDED_INQUIRY_RESPONSE <--\n");
            break;
        case HCI_EVENT_REMOTE_NAME_REQUEST_COMPLETE:
            reverse_bd_addr(&packet[3], event_addr);
            device = uni_hid_device_get_instance_for_address(event_addr);
            if (device != NULL) {
                if (packet[2] == 0) {
                    logi("Name: '%s'\n", &packet[9]);
                    device->state = REMOTE_NAME_FETCHED;
                } else {
                    logi("Failed to get name: page timeout\n");
                }
            }
            continue_remote_names();
            break;

        // L2CAP EVENTS
        case L2CAP_EVENT_INCOMING_CONNECTION:
            on_l2cap_incoming_connection(packet, channel);
            break;
        case L2CAP_EVENT_CHANNEL_OPENED:
            on_l2cap_channel_opened(packet, channel);
            break;
        case L2CAP_EVENT_CHANNEL_CLOSED:
            on_l2cap_channel_closed(packet, channel);
            break;

        // GAP EVENTS
        case GAP_EVENT_INQUIRY_RESULT:
            on_gap_inquiry_result(packet, channel);
            break;
        case GAP_EVENT_INQUIRY_COMPLETE:
            uni_hid_device_request_inquire();
            continue_remote_names();
            break;
        default:
            break;
        }
        break;
    case L2CAP_DATA_PACKET:
        // for now, just dump incoming data
        device = uni_hid_device_get_instance_for_cid(channel);
        if (device == NULL) {
            loge("Invalid cid: 0x%04x\n", channel);
            break;
        }
        if (channel == device->hid_interrupt_cid){
            logd("HID Interrupt Packet: ");
#if UNI_LOG_DEBUG
            printf_hexdump(packet, size);
#endif // UNI_LOG_DEBUG
            hid_parser_handle_interrupt_report(device, packet,  size);
        } else if (channel == device->hid_control_cid){
            logd("HID Control\n");
#if UNI_LOG_DEBUG            
            printf_hexdump(packet, size);
#endif
        } else {
            logi("Packet from unknown cid: 0x%04x\n", channel);
            printf_hexdump(packet, size);
            break;
        }
    default:
        break;
    }
}
static void on_hci_connection_request(uint8_t* packet, uint16_t channel) {
    bd_addr_t event_addr;
    uint32_t cod;
    uni_hid_device_t* device;
    UNUSED(channel);

    hci_event_connection_request_get_bd_addr(packet, event_addr);
    cod = hci_event_connection_request_get_class_of_device(packet);

    device = uni_hid_device_get_instance_for_address(event_addr);
    if (device == NULL) {
        device = uni_hid_device_create(event_addr);
        if (device == NULL) {
            logi("Cannot create new device... no more slots available\n");
            return;
        }
    }
    uni_hid_device_set_cod(device, cod);
    logi("on_hci_connection_request from: address = %s, cod=0x%04x\n", bd_addr_to_str(event_addr), cod);
}

static void on_gap_inquiry_result(uint8_t* packet, uint16_t channel) {
    bd_addr_t addr;
    uint8_t   status;
    uni_hid_device_t* device;

    UNUSED(channel);

    gap_event_inquiry_result_get_bd_addr(packet, addr);
    uint8_t page_scan_repetition_mode = gap_event_inquiry_result_get_page_scan_repetition_mode(packet);
    uint16_t clock_offset = gap_event_inquiry_result_get_clock_offset(packet);
    uint32_t cod = gap_event_inquiry_result_get_class_of_device(packet);

    logi("Device found: %s ",  bd_addr_to_str(addr));
    logi("with COD: 0x%06x, ", (unsigned int) cod);
    logi("pageScan %d, ",      page_scan_repetition_mode);
    logi("clock offset 0x%04x", clock_offset);
    if (gap_event_inquiry_result_get_rssi_available(packet)){
        logi(", rssi %d dBm", (int8_t) gap_event_inquiry_result_get_rssi(packet));
    }

    if (uni_hid_device_is_cod_supported(cod)) {
        device = uni_hid_device_get_instance_for_address(addr);
        if (device != NULL && !uni_hid_device_is_orphan(device)) {
            logi("... device already added\n");
            uni_hid_device_print_status(device);            
            return;
        }
        if (!device)
            device = uni_hid_device_create(addr);
        if (device == NULL) {
            loge("\nError: no more available device slots\n");
            return;
        }
        uni_hid_device_set_cod(device, cod);
        device->page_scan_repetition_mode = page_scan_repetition_mode;
        device->clock_offset = clock_offset;

        if (!uni_hid_device_has_name(device)) {
            if (gap_event_inquiry_result_get_name_available(packet)) {
                int name_len = gap_event_inquiry_result_get_name_len(packet);
                uni_hid_device_set_name(device, gap_event_inquiry_result_get_name(packet), name_len);
                logi(", name '%s'", device->name);
                device->state = REMOTE_NAME_FETCHED;;
            } else {
                device->state = REMOTE_NAME_REQUEST;
            }
        }
        logi("\n");
        status = l2cap_create_channel(packet_handler, device->address, PSM_HID_CONTROL, 48, &device->hid_control_cid);
        if (status){
            loge("\nConnecting to HID Control failed: 0x%02x", status);
        }
    }
    logi("\n");
}
static void on_l2cap_channel_opened(uint8_t* packet, uint16_t channel) {
    uint16_t psm;
    uint8_t status;
    uint16_t local_cid;
    uint16_t remote_cid;
    hci_con_handle_t handle;
    bd_addr_t address;
    uni_hid_device_t* device;
    uint8_t incoming;

    logi("L2CAP_EVENT_CHANNEL_OPENED (channel=0x%04x)\n", channel);
    
    l2cap_event_channel_opened_get_address(packet, address);
    status = l2cap_event_channel_opened_get_status(packet);
    if (status){
        logi("L2CAP Connection failed: 0x%02x. Removing previous link key.\n", status);
        uni_hid_device_remove_entry_with_channel(channel);
        // Just in case the key is outdated we remove it. If fixes some l2cap_channel_opened issues.
        // It proves that it works when the status is 0x6a (L2CAP_CONNECTION_BASEBAND_DISCONNECT).
        gap_drop_link_key_for_bd_addr(address);
        return;
    }
    psm = l2cap_event_channel_opened_get_psm(packet);
    local_cid = l2cap_event_channel_opened_get_local_cid(packet);
    remote_cid = l2cap_event_channel_opened_get_remote_cid(packet);
    handle = l2cap_event_channel_opened_get_handle(packet);
    incoming = l2cap_event_channel_opened_get_incoming(packet);
    logi("PSM: 0x%04x, Local CID=0x%04x, Remote CID=0x%04x, handle=0x%04x, incoming=%d\n", psm, local_cid, remote_cid, handle, incoming);

    device = uni_hid_device_get_instance_for_address(address);
    if (device == NULL) {
        loge("could not find device for address\n");
        uni_hid_device_remove_entry_with_channel(channel);
        return;
    }

    switch (psm){
    case PSM_HID_CONTROL:
        device->hid_control_cid = l2cap_event_channel_opened_get_local_cid(packet);
        logi("HID Control opened, cid 0x%02x\n", device->hid_control_cid);
        break;
    case PSM_HID_INTERRUPT:
        device->hid_interrupt_cid = l2cap_event_channel_opened_get_local_cid(packet);
        logi("HID Interrupt opened, cid 0x%02x\n", device->hid_interrupt_cid);
        // Don't request HID descriptor if we already have it.
        if (!uni_hid_device_has_hid_descriptor(device)) {
            sdp_query_hid_descriptor(device);
        }
        break;
    default:
        break;
    }

    if (!uni_hid_device_is_incoming(device)) {
        if (local_cid == 0) {
            loge("local_cid == 0. Abort\n");
            uni_hid_device_remove_entry_with_channel(channel);
            return;
        }
        if (local_cid == device->hid_control_cid) {
            logi("Creating HID INTERRUPT channel\n");
            status = l2cap_create_channel(packet_handler, device->address, PSM_HID_INTERRUPT, 48, &device->hid_interrupt_cid);
            if (status){
                loge("Connecting to HID Control failed: 0x%02x\n", status);
                uni_hid_device_remove_entry_with_channel(channel);
                return;
            }
            logi("New hid interrupt psm = 0x%04x\n", device->hid_interrupt_cid);
        }
        if (local_cid == device->hid_interrupt_cid) {
            logi("HID connection established\n");
        }
    }
}

static void on_l2cap_channel_closed(uint8_t* packet, uint16_t channel) {
    uint16_t local_cid;
    uni_hid_device_t* device;

    local_cid = l2cap_event_channel_closed_get_local_cid(packet);
    logi("L2CAP_EVENT_CHANNEL_CLOSED: 0x%04x (channel=0x%04x)\n", local_cid, channel);
    device = uni_hid_device_get_instance_for_cid(local_cid);
    if (device == NULL) {
        // Device might already been closed if the Control or Interrupt PSM was closed first.
        logi("Couldn't not find hid_device for cid = 0x%04x\n", local_cid);
        return;
    }
    uni_hid_device_set_disconnected(device);
}

static void on_l2cap_incoming_connection(uint8_t *packet, uint16_t channel) {
    bd_addr_t event_addr;
    uni_hid_device_t* device;
    uint16_t local_cid;
    uint16_t remote_cid;
    uint16_t psm;
    hci_con_handle_t handle;

    psm = l2cap_event_incoming_connection_get_psm(packet);
    handle = l2cap_event_incoming_connection_get_handle(packet);
    local_cid = l2cap_event_incoming_connection_get_local_cid(packet);
    remote_cid = l2cap_event_incoming_connection_get_remote_cid(packet);

    logi("L2CAP_EVENT_INCOMING_CONNECTION (psm=0x%04x, local_cid=0x%04x, remote_cid=0x%04x, handle=0x%04x, channel=0x%04x\n", psm, local_cid, remote_cid, handle, channel);
    switch (psm) {
        case PSM_HID_CONTROL:
            l2cap_event_incoming_connection_get_address(packet, event_addr);
            device = uni_hid_device_get_instance_for_address(event_addr);
            if (device == NULL) {
                device = uni_hid_device_create(event_addr);
                if (device == NULL) {
                    loge("ERROR: no more available free devices\n");
                    l2cap_decline_connection(channel);
                    break;
                }
            }
            l2cap_accept_connection(channel);
            device->con_handle = l2cap_event_incoming_connection_get_handle(packet);
            device->hid_control_cid = channel;
            uni_hid_device_set_incoming(device, 1);
            break;
        case PSM_HID_INTERRUPT:
            l2cap_event_incoming_connection_get_address(packet, event_addr);
            device = uni_hid_device_get_instance_for_address(event_addr);
            if (device == NULL) {
                loge("Could not find device for PSM_HID_INTERRUPT = 0x%04x\n", channel);
                l2cap_decline_connection(channel);
                break;
            }
            device->hid_interrupt_cid = channel;
            l2cap_accept_connection(channel);
            break;
        default:
            logi("Unknown PSM = 0x%02x\n", psm);
    }
}

static int has_more_remote_name_requests(void) {
    uni_hid_device_t* device;

    device = uni_hid_device_get_first_device_with_state(REMOTE_NAME_REQUEST);
    return (device != NULL);
}

static void do_next_remote_name_request(void) {
    uni_hid_device_t* device;

    device = uni_hid_device_get_first_device_with_state(REMOTE_NAME_REQUEST);
    if (device != NULL) {
        device->state = REMOTE_NAME_INQUIRED;
        logi("Get remote name of %s...\n", bd_addr_to_str(device->address));
        gap_remote_name_request( device->address, device->page_scan_repetition_mode,  device->clock_offset | 0x8000);
    }
}

static void continue_remote_names(void) {
    if (has_more_remote_name_requests()) {
        do_next_remote_name_request();
        return;
    }
    start_scan();
}

static void start_scan(void) {
    logi("Starting inquiry scan..\n");
    gap_inquiry_start(INQUIRY_INTERVAL);
}

static void sdp_query_hid_descriptor(uni_hid_device_t* device) {
    logi("Starting SDP query for HID descriptor for: %s\n", bd_addr_to_str(device->address));
    // Needed for the SDP query since it only supports oe SDP query at the time.
    uni_hid_device_t* current = uni_hid_device_get_current_device();
    if (current != NULL) {
        loge("Error: Ouch, another SDP query is in progress (%s) Try again later.\n", bd_addr_to_str(current->address));
        return;
    }

    uni_hid_device_set_current_device(device);
    uint8_t status = sdp_client_query_uuid16(&handle_sdp_hid_query_result, device->address, BLUETOOTH_SERVICE_CLASS_HUMAN_INTERFACE_DEVICE_SERVICE);
    if (status != 0) {
        uni_hid_device_set_current_device(NULL);
        loge("Failed to perform sdp query\n");
    }
}

static void sdp_query_product_id(uni_hid_device_t* device) {
    logi("Starting SDP query for product/vendor ID\n");
    uni_hid_device_t* current = uni_hid_device_get_current_device();
    // This query runs after sdp_query_hid_descriptor() so uni_hid_device_get_current_device() must not be NULL
    if (current == NULL) {
        loge("Error: current device is NULL. Should not happen\n");
        return;
    }
    uint8_t status = sdp_client_query_uuid16(&handle_sdp_did_query_result, device->address, BLUETOOTH_SERVICE_CLASS_PNP_INFORMATION);
    if (status != 0) {
        uni_hid_device_set_current_device(NULL);
        loge("Failed to perform SDP DeviceID query\n");
    }
}

static void list_link_keys(void) {
    bd_addr_t  addr;
    link_key_t link_key;
    link_key_type_t type;
    btstack_link_key_iterator_t it;

    int ok = gap_link_key_iterator_init(&it);
    if (!ok) {
        loge("Link key iterator not implemented\n");
        return;
    }
    logi("Stored link keys: \n");
    while (gap_link_key_iterator_get_next(&it, addr, link_key, &type)){
        logi("%s - type %u, key: ", bd_addr_to_str(addr), (int) type);
        printf_hexdump(link_key, 16);
        // gap_drop_link_key_for_bd_addr(addr);
    }
    logi(".\n");
    gap_link_key_iterator_done(&it);
}

int btstack_main(int argc, const char * argv[]) {

    (void)argc;
    (void)argv;

    // Honoring with BT copyright + adding own message to avoid confusion
    printf("Unijoysticle (C) 2016-2019 Ricardo Quesada and contributors.\n");
    printf("Bluetooth stack: Copyright (C) 2017 BlueKitchen GmbH.\n");
    printf("Firmware version: v0.0.1\n");

    gpio_joy_init();
    uni_hid_device_init();

    // Initialize L2CAP
    l2cap_init();

    hid_host_setup();

    // btstack_stdin_setup(stdin_process);
    // Turn on the device
    hci_power_control(HCI_POWER_ON);
    return 0;
}

/* EXAMPLE_END */
