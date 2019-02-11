
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

#include "uni_gamepad.h"

#include "uni_debug.h"

void uni_gamepad_dump(uni_gamepad_t* gamepad) {
    logi("(0x%04x) dpad=0x%02x, x=%d, y=%d, rx=%d, ry=%d, accel=%d, brake=%d, buttons=0x%08x, misc=0x%02x\n",
        gamepad->updated_states,
        gamepad->dpad,
        gamepad->x, gamepad->y,
        gamepad->rx, gamepad->ry,
        gamepad->accelerator, gamepad->brake,
        gamepad->buttons,
        gamepad->misc_buttons);
}
