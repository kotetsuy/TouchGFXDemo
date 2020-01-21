//LCD Manager module for HX8347D on TouchGFX
//Support writing active area configuration data
//and sending framebuffer block data on DMA

#include "ili9341.h"
#include "LCDManager.h"

extern void LCDManager_TransferComplete();

static __IO uint8_t isTransmittingData = 0;

uint32_t LCDManager_IsTransmittingData(void)
{
	return isTransmittingData;
}

void LCDManager_SendFrameBufferBlockWithPosition(uint8_t* pixels, uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
	isTransmittingData = 1;
	ILI9341_SetWindow(x, y, x+w-1, y+h-1);
	ILI9341_DrawBitmap(w, h, pixels);
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
	if (hspi->Instance == SPI1) {
		ILI9341_EndOfDrawBitmap();
		isTransmittingData = 0;
		LCDManager_TransferComplete();
	}
}
