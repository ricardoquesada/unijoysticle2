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

// ESP32 version

#include "gpio_joy.h"

#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "driver/gpio.h"

#include "uni_debug.h"
#include "my_hid_device.h"

// GPIO map for MH-ET Live mini-kit board.
// Same GPIOs as Wemos D1 mini (used in Unijoysticle v0.4)
enum {
    GPIO_JOY_A_UP       = GPIO_NUM_26,      // D0
    GPIO_JOY_A_DOWN     = GPIO_NUM_22,      // D1
    GPIO_JOY_A_LEFT     = GPIO_NUM_21,      // D2
    GPIO_JOY_A_RIGHT    = GPIO_NUM_17,      // D3
    GPIO_JOY_A_FIRE     = GPIO_NUM_16,      // D4

    GPIO_JOY_B_UP       = GPIO_NUM_18,      // D5
    GPIO_JOY_B_DOWN     = GPIO_NUM_19,      // D6
    GPIO_JOY_B_LEFT     = GPIO_NUM_23,      // D7
    GPIO_JOY_B_RIGHT    = GPIO_NUM_5,       // D8
    // GPIO_NUM_3 is assigned to the UART. And although it is possible to
    // rewire the GPIOs for the UART in software, the devkits expects that GPIOS 1 and 3
    // are assigned to UART 0. And I cannot use it.
    // Using GPIO 27 instead, which is the one that is closer to GPIO 3.
    GPIO_JOY_B_FIRE     = GPIO_NUM_27,      // RX
};

enum {
    EVENT_BIT_JOYSTICK = (1 << 0),
};

static const int MOUSE_DELAY_BETWEEN_EVENT_US = 12000;  // microseconds
static const int MOUSE_MAX_DELTA = 32;

static gpio_num_t JOY_A_PORTS[] = {GPIO_JOY_A_UP, GPIO_JOY_A_DOWN, GPIO_JOY_A_LEFT, GPIO_JOY_A_RIGHT, GPIO_JOY_A_FIRE};
static gpio_num_t JOY_B_PORTS[] = {GPIO_JOY_B_UP, GPIO_JOY_B_DOWN, GPIO_JOY_B_LEFT, GPIO_JOY_B_RIGHT, GPIO_JOY_B_FIRE};

// Mouse related
static EventGroupHandle_t g_mouse_event_group;

static void gpio_joy_update_port(joystick_t* joy, gpio_num_t* gpios);
static void mouse_loop(void* arg);
static void send_move(int pin_a, int pin_b, uint32_t delay);
static void move_x(int dir, uint32_t delay);
static void move_y(int dir, uint32_t delay);
static void delay_us(uint32_t delay);

// Mouse "shared data from main task to mouse task.
static int32_t g_delta_x = 0;
static int32_t g_delta_y = 0;

 #define MAX(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

 #define MIN(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })     

void gpio_joy_init(void) {
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    // Port A.
    io_conf.pin_bit_mask = (
        (1ULL << GPIO_JOY_A_UP) | (1ULL << GPIO_JOY_A_DOWN) |
        (1ULL << GPIO_JOY_A_LEFT) | (1ULL << GPIO_JOY_A_RIGHT) |
        (1ULL << GPIO_JOY_A_FIRE)
        );
    // Port B.
    io_conf.pin_bit_mask |= (
        (1ULL << GPIO_JOY_B_UP) | (1ULL << GPIO_JOY_B_DOWN) |
        (1ULL << GPIO_JOY_B_LEFT) | (1ULL << GPIO_JOY_B_RIGHT) |
        (1ULL << GPIO_JOY_B_FIRE)
        );

    ESP_ERROR_CHECK( gpio_config(&io_conf) );

    // Set low all GPIOs... just in case.
    const int MAX_GPIOS = sizeof(JOY_A_PORTS)/sizeof(JOY_A_PORTS[0]);
    for (int i=0; i<MAX_GPIOS; i++) {
        ESP_ERROR_CHECK( gpio_set_level(JOY_A_PORTS[i], 0));
        ESP_ERROR_CHECK( gpio_set_level(JOY_B_PORTS[i], 0));
    }

    // Mouse related
    g_mouse_event_group = xEventGroupCreate();
    xTaskCreate(mouse_loop, "mouse_loop", 2048, NULL, 10, NULL);
}

void gpio_joy_update_mouse(int32_t delta_x, int32_t delta_y) {
#if ENABLE_VERBOSE_LOG
    printf("mouse x=%d, y=%d\n", delta_x, delta_y);
#endif // ENABLE_VERBOSE_LOG

    // Mouse is implemented using a quadrature encoding
    // FIXMI: Passing values to mouse task using global variables. This is, of course,
    // error-prone to raaces and what not, but seeems to be good enough for our purpose.
    if (delta_x || delta_y) {
        g_delta_x = delta_x;
        g_delta_y = delta_y;
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        xEventGroupSetBitsFromISR(g_mouse_event_group, EVENT_BIT_JOYSTICK, &xHigherPriorityTaskWoken);
    }
}

void gpio_joy_update_port_a(joystick_t* joy) {
    gpio_joy_update_port(joy, JOY_A_PORTS);
}

void gpio_joy_update_port_b(joystick_t* joy) {
    gpio_joy_update_port(joy, JOY_B_PORTS);
}

static void gpio_joy_update_port(joystick_t* joy, gpio_num_t* gpios) {
#if ENABLE_VERBOSE_LOG
    printf("up=%d, down=%d, left=%d, right=%d, fire=%d\n",
        joy->up, joy->down, joy->left, joy->right, joy->fire);
#endif // ENABLE_VERBOSE_LOG

    gpio_set_level(gpios[0], !!joy->up);
    gpio_set_level(gpios[1], !!joy->down);
    gpio_set_level(gpios[2], !!joy->left);
    gpio_set_level(gpios[3], !!joy->right);
    gpio_set_level(gpios[4], !!joy->fire);
}

// Mouse handler
void mouse_loop(void* arg) {
    (void)arg;

    // timeout of 10s
    const TickType_t xTicksToWait = 10000 / portTICK_PERIOD_MS;
    while(1) {
        EventBits_t uxBits = xEventGroupWaitBits(g_mouse_event_group, EVENT_BIT_JOYSTICK, pdTRUE, pdFALSE, xTicksToWait);

        // Exit by timeout ? then just continue.
        if (uxBits == 0)
            continue;

        // Should not happen, but better safe than sorry
        if (g_delta_x == 0 && g_delta_y == 0)
            return;

        // Based on the deltas, generate a line. It uses Bresenham-sort-of algorithm.
        // We consider these 4 cases:
        // Y = 0, X = 0, X > Y, Y > X
        // Any delta greater than MOUSE_MAX_DELTA is capped to MOUSE_MAX_DELTA
        int abs_x = abs(g_delta_x);
        if (abs_x > 2)
            abs_x = MIN(15, MAX(1, abs_x >> 3));
        int abs_y = abs(g_delta_y);
        if (abs_y > 2)
            abs_y = MIN(15, MAX(1, abs_y >> 3));

        // dir_x / dir_y have the same values as the global delta, but they are easy
        // to understand its meaning when being passed to move_x() / move_y().
        int dir_x = g_delta_x;
        int dir_y = g_delta_y;
        // Y = 0
        if (abs_x != 0 && abs_y == 0) {
            // Horizontal movment
            // The faster it moves, the less delay it has.
            uint32_t delay = (MOUSE_DELAY_BETWEEN_EVENT_US / abs_x) + 1;
            for (int i=0; i<abs_x;i++) {
                move_x(dir_x, delay);
            }
        }
        // X = 0
        else if (abs_x == 0 && abs_y !=0 ) {
            // Vertical movement
            // The faster it moves, the less delay it has.
            uint32_t delay = (MOUSE_DELAY_BETWEEN_EVENT_US / abs_y) + 1;
            for (int i=0; i<abs_y;i++) {
                move_y(dir_y, delay);
            }
        }
        else if (abs_x > abs_y) {
            // X is the driving the loop.
            uint32_t delay = (MOUSE_DELAY_BETWEEN_EVENT_US / (abs_x+abs_y)) + 1;
            // Avoid floating points to make it more portable between microcontrollers.
            int inc_y = abs_y * 100 / abs_x;
            int accum_y = 0;

            for (int i=0; i<abs_x;i++) {
                move_x(dir_x, delay);
                accum_y += inc_y;
                if (accum_y >= 100) {
                    move_y(dir_y, delay);
                    accum_y -= 100;
                }
            }
        }
        else  {
            // Y is the driving the loop.
            uint32_t delay = (MOUSE_DELAY_BETWEEN_EVENT_US / (abs_x+abs_y)) + 1;
            // Avoid floating points to make it more portable between microcontrollers.
            int inc_x = abs_x * 100 / abs_y;
            int accum_x = 0;

            for (int i=0; i<abs_y; i++) {
                move_y(dir_y, delay);
                accum_x += inc_x;
                if (accum_x >= 100) {
                    move_x(dir_x, delay);
                    accum_x -= 100;
                }
            }
        }
    }
}

static void send_move(int pin_a, int pin_b, uint32_t delay) {
    gpio_set_level(pin_a, 1);
    delay_us(delay);
    gpio_set_level(pin_b, 1);
    delay_us(delay);

    gpio_set_level(pin_a, 0);
    delay_us(delay);
    gpio_set_level(pin_b, 0);
    delay_us(delay);
}

static void move_x(int dir, uint32_t delay) {
    // up, down, left, right, fire
    if (dir < 0)
        send_move(JOY_A_PORTS[0], JOY_A_PORTS[1], delay);
    else
        send_move(JOY_A_PORTS[1], JOY_A_PORTS[0], delay);
}

static void move_y(int dir, uint32_t delay) {
    // up, down, left, right, fire
    if (dir < 0)
        send_move(JOY_A_PORTS[2], JOY_A_PORTS[3], delay);
    else
        send_move(JOY_A_PORTS[3], JOY_A_PORTS[2], delay);
}

// Delay in microseconds. Anything bigger than 1000 microseconds (1 millisecond)
// should be scheduled using vTaskDelay(), which will allow context-switch and allow
// other tasks to run.
static void delay_us(uint32_t delay) {
    if (delay > 1000)
        vTaskDelay(delay / 1000);
    else
        ets_delay_us(delay);
}
