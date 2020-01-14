/*
 * bridge.cpp
 *
 *  Created on: Jan 14, 2020
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
#include <touchgfx/hal/HAL.hpp>
#include "app_touchgfx.h"

using namespace touchgfx;

#include "main.h"
#include "cmsis_os.h"
#include "ili9341.h"

static int8_t Running;

uint8_t isTransmittingData(void)
{
	return Running;
}

void transmitFrameBufferBlock(uint8_t* pixels, uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
	ILI9341_SetWindow(x, y, x+w-1, y+h-1);
	ILI9341_DrawBitmap(w, h, pixels);
}

void startNewTransfer(void)
{
    FrameBufferAllocator* fba = HAL::getInstance()->getFrameBufferAllocator();
    fba->freeBlockAfterTransfer();
	Running = 1;

    if (fba->hasBlockReadyForTransfer())
    {
        touchgfx::Rect r;
        const uint8_t* pixels = fba->getBlockForTransfer(r);
        transmitFrameBufferBlock((uint8_t*)pixels, r.x, r.y, r.width, r.height);
    }
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
	if (hspi->Instance == SPI1){
		Running = 0;
		startNewTransfer();
	}
}

