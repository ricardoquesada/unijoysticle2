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

// Stub version

#include "uni_gpio.h"

#include <stdio.h>

static void print_joystick(joystick_t* joy) {
  printf("up=%d, down=%d, left=%d, right=%d, fire=%d, potx=%d, poty=%d\n", joy->up, joy->down, joy->left, joy->right,
         joy->fire, joy->pot_x, joy->pot_y);
}

void uni_gpio_init(void) {}

void uni_gpio_update_port_a(joystick_t* joy) {
  print_joystick(joy);
}

void uni_gpio_update_port_b(joystick_t* joy) {
  print_joystick(joy);
}

void uni_gpio_update_mouse(int32_t delta_x, int32_t delta_y) {
  printf("mouse: x=%d, y=%d\n", delta_x, delta_y);
}