/*
 * gui.c
 *
 *  Created on: Jan 2, 2020
 *      Author: Kotetsu Yamamoto
 *      Copyright: Kotetsu Yamamoto

MIT License

Copyright (c) 2020 Kotestu Yamamoto

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

 */

#include "main.h" // Hardware setting
#include "gui.h"
#include "ili9341.h"
#include "xpt2046.h"

#define MAXTXH 80

static uint8_t vvram[GUI_HEIGHT*GUI_WIDTH*sizeof(uint16_t)]; // Virtual Video RAM Big endian for 1 line
static __IO uint8_t Done;

void GUI_FillScreen(uint16_t cl)
{
	for (uint32_t x = 0; x < GUI_HEIGHT*GUI_WIDTH*2;) {
		vvram[x++] = cl >> 8;
		vvram[x++] = cl;
	}
}

void GUI_WritePixel(uint16_t x, uint16_t y, uint16_t cl)
{
	vvram[y*GUI_WIDTH*sizeof(uint16_t) + x*sizeof(uint16_t)] = cl >> 8;
	vvram[y*GUI_WIDTH*sizeof(uint16_t) + x*sizeof(uint16_t) + 1] = cl;
	ILI9341_WritePixel(x,y,cl);
}

void GUI_WriteSquare(uint16_t x, uint16_t y, uint16_t cl)
{
	static uint8_t bmp[5*5*2];
	int16_t x1, y1, x2, y2;
	for (int32_t i = 0; i < 25; i++) {
		bmp[i*2] = cl >>8;
		bmp[i*2] = cl;
	}
	x1 = x - 2;
	y1 = y - 2;
	x1 = (x1 < 0) ? 0 : x1;
	y1 = (y1 < 0) ? 0 : y1;
	x2 = x + 2;
	y2 = y + 2;
	x2 = (x2 >= GUI_WIDTH) ? GUI_WIDTH-1 : x2;
	y2 = (y2 >= GUI_HEIGHT) ? GUI_HEIGHT-1 : y2;
	for (int32_t i = y1; i <= y2; i++) {
		for (int32_t j = x1; j <= x2; j++) {
			vvram[i*GUI_WIDTH*sizeof(uint16_t) + j*sizeof(uint16_t)] = cl >> 8;
			vvram[i*GUI_WIDTH*sizeof(uint16_t) + j*sizeof(uint16_t) + 1] = cl;
		}
	}
	ILI9341_SetWindow(x1, y1, x2, y2);
	ILI9341_DrawBitmap(x2-x1+1, y2-y1+1, bmp);
}

void GUI_UpdateScreen(void)
{
	// HAL_SPI_Transmit_DMA supports the translation size until 0xffff
	// So, I need to separate bitmap
	for (uint32_t y = 0; y < GUI_HEIGHT; y += MAXTXH) {
		ILI9341_SetWindow(0, y, GUI_WIDTH-1, y+MAXTXH-1);
		Done = 0;
		ILI9341_DrawBitmap(GUI_WIDTH, MAXTXH, &vvram[y*GUI_WIDTH*sizeof(uint16_t)]);
		while (Done == 0)
			;
	}
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
	if (hspi->Instance == SPI1) {
		Done = 1;
	}
}

void GUI_NormalizeXY(int16_t *x, int16_t *y)
{
	*x = (int16_t)((int32_t)(*x - XPT_XMIN) * GUI_WIDTH / XPT_WIDTH);
	*x = (*x < 0) ? 0 : *x;
	*x = (*x >= GUI_WIDTH) ? GUI_WIDTH-1 : *x;
	*y = (int16_t)((int32_t)(*y - XPT_YMIN) * GUI_HEIGHT / XPT_HEIGHT);
	*y = (*y < 0) ? 0 : *y;
	*y = (*y >= GUI_HEIGHT) ? GUI_HEIGHT-1 : *y;
}
