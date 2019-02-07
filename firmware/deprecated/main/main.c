/****************************************************************************
http://retro.moe/unijoysticle

Copyright 2017 Ricardo Quesada

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

#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"

#include "esp_wifi.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_event_loop.h"

#include "nvs_flash.h"

#include "driver/gpio.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"

//
// contants
//
static const int WIFI_CONNECTED_BIT = 1 << 0;
static const int POT_PORT1_BIT = 1 << 0;
static const int POT_PORT2_BIT = 1 << 1;
static const int BUFSIZE = 512;
static const unsigned short UDP_PORT = 6464;


//
// global variables
//
static EventGroupHandle_t g_pot_event_group, g_wifi_event_group;
static struct uni_proto_v3 g_joy_state;


//
// structs
//
struct uni_proto_v3
{
    char version;
    char ports_enabled;
    char joy1;
    char joy2;
    char joy1_potx;
    char joy1_poty;
    char joy2_potx;
    char joy2_poty;
};

void IRAM_ATTR gpio_isr_handler_up(void* arg)
{
    uint32_t gpio_num = (uint32_t) arg;
    (void)gpio_num;

    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xEventGroupSetBitsFromISR(g_pot_event_group, POT_PORT1_BIT, &xHigherPriorityTaskWoken);

    portYIELD_FROM_ISR();
}

void main_loop(void* arg)
{
    (void)arg;

    // timeout of 500ms
    const TickType_t xTicksToWait = 500 / portTICK_PERIOD_MS;
    while(1) {

        EventBits_t uxBits = xEventGroupWaitBits(g_pot_event_group, (POT_PORT1_BIT | POT_PORT2_BIT), pdTRUE, pdFALSE, xTicksToWait);
//        xEventGroupClearBits(g_pot_event_group, (POT_PORT1_BIT | POT_PORT2_BIT));

        // if not timeout, change the state
        if (uxBits != 0) {

//            gpio_set_level(GPIO_NUM_5, 0);

//            gpio_set_level(GPIO_NUM_21, 1);
//            ets_delay_us(50);
            gpio_set_level(GPIO_NUM_21, 0);

            ets_delay_us(223);
            ets_delay_us(g_joy_state.joy1_potx);

            gpio_set_level(GPIO_NUM_21, 1);
//            gpio_set_level(GPIO_NUM_5, 1);

//            ets_delay_us(50);

//            gpio_set_level(GPIO_NUM_21, 0);

//            gpio_set_level(GPIO_NUM_5, 0);


//            const TickType_t xDelay = 100 / portTICK_PERIOD_MS;
//            vTaskDelay(xDelay);
        } else {
            // timeout
            gpio_set_level(GPIO_NUM_21, 0);
        }

//        taskYIELD();
    }
}

void wifi_loop(void* arg)
{
    /* Wait for internet to be up */
    xEventGroupWaitBits(g_wifi_event_group, WIFI_CONNECTED_BIT, false, true, portMAX_DELAY);

    int sockfd;                         /* socket */
    socklen_t clientlen;                /* byte size of client's address */
    struct sockaddr_in serveraddr;      /* server's addr */
    struct sockaddr_in clientaddr;      /* client addr */
    char buf[BUFSIZE];                  /* message buf */
    int n;                              /* message byte size */

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
        printf("ERROR opening socket");

    /* build the server's Internet address */
    memset((char *) &serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(UDP_PORT);

    if (bind(sockfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0)
        printf("ERROR on binding\n");

    clientlen = sizeof(clientaddr);

    while (1) {

        n = recvfrom(sockfd, buf, BUFSIZE, 0, (struct sockaddr *) &clientaddr, &clientlen);
        if (n == 8) {
            const struct uni_proto_v3 *proto = (struct uni_proto_v3*) &buf;
            g_joy_state = *proto;
        }
    }
}

void test_loop(void* arg)
{
    ESP_ERROR_CHECK( gpio_set_direction(GPIO_NUM_22, GPIO_MODE_OUTPUT) );
    ESP_ERROR_CHECK( gpio_set_level(GPIO_NUM_22, 0) );

    while (1) {
        /* Block for 500ms. */
         const TickType_t xDelay = 10 / portTICK_PERIOD_MS;
        vTaskDelay(xDelay);
        gpio_set_level(GPIO_NUM_22, true);
        vTaskDelay(xDelay);
        gpio_set_level(GPIO_NUM_22, false);

    }
}

esp_err_t event_handler(void *ctx, system_event_t *event)
{
    switch(event->event_id) {
        case SYSTEM_EVENT_STA_START:
            printf("SYSTEM_EVENT_STA_START\n");
            esp_wifi_connect();
            break;
        case SYSTEM_EVENT_STA_GOT_IP:
            printf("SYSTEM_EVENT_STA_GOT_IP\n");
            xEventGroupSetBits(g_wifi_event_group, WIFI_CONNECTED_BIT);
            break;
        case SYSTEM_EVENT_STA_DISCONNECTED:
            printf("SYSTEM_EVENT_STA_DISCONNECTED\n");
            /* This is a workaround as ESP32 WiFi libs don't currently auto-reassociate. */
            esp_wifi_connect();
            xEventGroupClearBits(g_wifi_event_group, WIFI_CONNECTED_BIT);
            break;
        default:
            break;
    }
    return ESP_OK;
}

static void setup_gpios()
{
    // Input:
    //     4: Joy #2 Pot x
    //
    // Output:
    //     5: Joy #1 Pot X
    //    21: Joy #1 Pot X

    // Output: 5 (LED) and 21
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = ((1ULL << GPIO_NUM_21) | (1ULL << GPIO_NUM_5));
    io_conf.pull_down_en = false;
    io_conf.pull_up_en = false;
    ESP_ERROR_CHECK( gpio_config(&io_conf) );

    // Input: read POT X
    io_conf.intr_type = GPIO_INTR_POSEDGE;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = 1ULL << GPIO_NUM_18;
    io_conf.pull_down_en = false;
    io_conf.pull_up_en = true;
    ESP_ERROR_CHECK( gpio_config(&io_conf) );

    // install gpio isr service
    ESP_ERROR_CHECK( gpio_install_isr_service(0) );

    //hook isr handler for specific gpio pin
    ESP_ERROR_CHECK( gpio_isr_handler_add(GPIO_NUM_18, gpio_isr_handler_up, (void*) GPIO_NUM_18) );

 //   ESP_ERROR_CHECK( gpio_isr_register(gpio_isr_handler_up, (void*) GPIO_NUM_4, 0, NULL) );
}

static void setup_wifi()
{
    tcpip_adapter_init();
    ESP_ERROR_CHECK( esp_event_loop_init(event_handler, NULL) );
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK( esp_wifi_init(&cfg) );
    ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_RAM) );
    ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_STA) );
    wifi_config_t sta_config = {
        .sta = {
            .ssid = "queque2",
            .password = "locopajaro",
            .bssid_set = false
        }
    };
    ESP_ERROR_CHECK( esp_wifi_set_config(WIFI_IF_STA, &sta_config) );
    ESP_ERROR_CHECK( esp_wifi_start() );
    ESP_ERROR_CHECK( esp_wifi_connect() );
}

static void setup_variables()
{
    memset(&g_joy_state, 0, sizeof(g_joy_state));
}

void app_main(void)
{
    nvs_flash_init();

    g_pot_event_group = xEventGroupCreate();
    g_wifi_event_group = xEventGroupCreate();

    setup_variables();
    setup_wifi();
    setup_gpios();

    printf("v3 size: %d\n", sizeof(struct uni_proto_v3));

    xTaskCreate(main_loop, "main_loop", 2048, NULL, 10, NULL);
    xTaskCreate(wifi_loop, "wifi_loop", 2048, NULL, 10, NULL);
//    xTaskCreate(test_loop, "test_loop", 2048, NULL, 10, NULL);

//    main_loop(NULL);
}

