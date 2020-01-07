/*
 * touch.h
 *
 *  Created on: Jan 6, 2020
 *      Author: Kotetsu Yamamoto
 *      Copyright [Kotetsu Yamamoto]

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

 */

#ifndef INC_TOUCH_H_
#define INC_TOUCH_H_

#include "main.h"

#define TP_PRES_DOWN 0x80
#define TP_CATH_PRES 0x40
#define CMD_RDX 0xD0
#define CMD_RDY 0x90

uint16_t XPT2046_Read_XOY(uint8_t xy);
uint8_t XPT2046_Scan(void);
uint8_t XPT2046_GetStatus(void);

#endif /* INC_TOUCH_H_ */
