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

#ifndef UNI_CONFIG_H
#define UNI_CONFIG_H

// How verbose the logging should be.
// It is safe to leave UNI_LOG_DEBUG disabled (unless you are a developer).
#define UNI_LOG_ERROR 1
#define UNI_LOG_INFO 1
#define UNI_LOG_DEBUG 0

// Enable pin compatibility with Unijoysticle v1 pinout. Enable this if you have
// a Unijoysticle v1 (the one with ESP8266) and want to replace the ESP8266 with
// an ESP32. If you are Esteban/Arleka most probably you want this enabled.
#define UNI_ENABLE_COMPAT_V1 0  // Enabled if 1

// Enable C64 POT support. Currently not implemented
#define UNI_ENABLE_POT 0  // Enabled if 1

// Enable Amiga/Atari ST mouse support.
#define UNI_ENABLE_MOUSE 1  // Enabled if 1

#endif  // UNI_CONFIG_H