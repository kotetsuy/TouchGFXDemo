/*
 * gui.c
 *
 *  Created on: Jan 2, 2020
 *      Author: Kotetsu Yama
 *      Copyright: Kotetsu Yama

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

#include "main.h" // Hardware setting
#include "gui.h"
#include "ili9341.h"
#include <string.h>

static uint8_t vvram[GUI_WIDTH*sizeof(uint16_t)]; // Virtual Video RAM Big endian for 1 line
static __IO uint8_t Done;

void GUI_FillScreen(uint16_t cl)
{
	for (uint16_t x = 0; x < GUI_WIDTH*2;) {
		vvram[x++] = cl >> 8;
		vvram[x++] = cl;
	}
	for (uint16_t y = 0; y < GUI_HEIGHT; y++) {
		ILI9341_SetWindow(0, y, GUI_WIDTH-1, y);
		Done = 0;
		ILI9341_DrawBitmap(GUI_WIDTH, 1, vvram);
		while (Done == 0)
			;
	}
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
	Done = 1;
}

void GUI_WritePixel(uint16_t x, uint16_t y, uint16_t cl)
{
	ILI9341_WritePixel(x,y,cl);
}
