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

// Stub version

#include "uni_platform.h"

#include <stdio.h>
#include <string.h>

static void print_joystick(char joy_port, uni_joystick_t* joy) {
  static uni_joystick_t prev_joy = {.auto_fire = 255};
  if (memcmp(joy, &prev_joy, sizeof(*joy)) != 0) {
    printf(
        "Joy %c: up=%d, down=%d, left=%d, right=%d, fire=%d, potx=%d, poty=%d, "
        "autofire=%d\n",
        joy_port, joy->up, joy->down, joy->left, joy->right, joy->fire,
        joy->pot_x, joy->pot_y, joy->auto_fire);
    memcpy(&prev_joy, joy, sizeof(prev_joy));
  }
}
void uni_platform_init(void) {}
void uni_platform_on_joy_a_data(uni_joystick_t* joy) {
  print_joystick('A', joy);
}
void uni_platform_on_joy_b_data(uni_joystick_t* joy) {
  print_joystick('B', joy);
}
void uni_platform_on_mouse_data(int32_t delta_x, int32_t delta_y,
                                uint16_t buttons) {
  printf("mouse: x=%d, y=%d, buttons=0x%4x\n", delta_x, delta_y, buttons);
}

uint8_t uni_platform_is_button_pressed() { return 0; }

// Events.
void uni_platform_on_init_complete(void) {}
void uni_platform_on_port_assign_changed(uni_joystick_port_t port) {
  uint8_t port_status_a = ((port & JOYSTICK_PORT_A) == JOYSTICK_PORT_A);
  uint8_t port_status_b = ((port & JOYSTICK_PORT_B) == JOYSTICK_PORT_B);
  printf("LED A = %d, LED B = %d\n", port_status_a, port_status_b);
}