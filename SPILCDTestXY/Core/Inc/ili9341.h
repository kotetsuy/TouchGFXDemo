/*
 * ili9341.h
 *
 *  Created on: 2019/12/26
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

#ifndef INC_ILI9341_H_
#define INC_ILI9341_H_

#include "main.h" // For STM32F4

#define WHITE       	0xFFFF
#define BLACK      		0x0000
#define BLUE       		0x001F
#define BRED        	0XF81F
#define GRED 			0XFFE0
#define GBLUE			0X07FF
#define RED         	0xF800
#define MAGENTA     	0xF81F
#define GREEN       	0x07E0
#define CYAN        	0x7FFF
#define YELLOW      	0xFFE0
#define BROWN 			0XBC40
#define BRRED 			0XFC07
#define GRAY  			0X8430
#define DARKBLUE      	0X01CF
#define LIGHTBLUE      	0X7D7C
#define GRAYBLUE       	0X5458
#define LIGHTGREEN     	0X841F
#define LIGHTGRAY     	0XEF5B
#define LGRAY 			0XC618
#define LGRAYBLUE      	0XA651
#define LBBLUE          0X2B12


void ILI9341_Init(void);
void ILI9341_SetWindow(uint16_t start_x, uint16_t start_y, uint16_t end_x, uint16_t end_y);
void ILI9341_DrawBitmap(uint16_t w, uint16_t h, uint8_t *s);
void ILI9341_WritePixel(uint16_t x, uint16_t y, uint16_t color);

#endif /* INC_ILI9341_H_ */
