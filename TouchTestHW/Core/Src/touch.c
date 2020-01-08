/*
 * touch.c
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

#include "touch.h"

// I refer https://github.com/dtnghia2206/TFTLCD/blob/master/TFTLCD/Touch/Touch.c


#define T_IRQ XPT2046_ReadIRQ()
#define T_CS_ON XPT2046_SetCS()
#define T_CS_OFF XPT2046_ResetCS()

#define READ_TIMES 	5
#define LOST_VAL 	1
#define ERR_RANGE 50

extern SPI_HandleTypeDef hspi3;
extern void Error_Handler(void);

static uint8_t status = 0;
static uint16_t x = 0;
static uint16_t y = 0;
static uint16_t x0 = 0;
static uint16_t y0 = 0;

static GPIO_PinState XPT2046_ReadIRQ(void)
{
	return HAL_GPIO_ReadPin(T_IRQ_GPIO_Port, T_IRQ_Pin);
}

static void XPT2046_SetCS(void)
{
	HAL_GPIO_WritePin(T_CS_GPIO_Port, T_CS_Pin, GPIO_PIN_SET);
}

static void XPT2046_ResetCS(void)
{
	HAL_GPIO_WritePin(T_CS_GPIO_Port, T_CS_Pin, GPIO_PIN_RESET);
}

static void XPT2046_Write_Byte(uint8_t num)
{
#if 0
	hspi3.Instance = SPI3;
	hspi3.Init.Mode = SPI_MODE_MASTER;
	hspi3.Init.Direction = SPI_DIRECTION_2LINES;
	hspi3.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi3.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi3.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi3.Init.NSS = SPI_NSS_SOFT;
	hspi3.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
	hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi3.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi3.Init.CRCPolynomial = 10;

	if (HAL_SPI_Init(&hspi3) != HAL_OK)
	{
		Error_Handler();
	}
#else
	hspi3.Instance->CR2 &= ~(SPI_DATASIZE_16BIT); // Set 8 bit mode
	__HAL_SPI_ENABLE(&hspi3);
#endif
	if (HAL_SPI_Transmit(&hspi3, &num, 1, 1000) != HAL_OK) {
		Error_Handler();
	}
#if 0
	HAL_SPI_DeInit(&hspi3);
#else
	__HAL_SPI_DISABLE(&hspi3);
#endif
}

static uint16_t XPT2046_Read_AD(uint8_t CMD)
{
	uint8_t num[2];
	uint16_t ret;

	T_CS_OFF;
	XPT2046_Write_Byte(CMD);
	HAL_Delay(6);

#if 0
	hspi3.Instance = SPI3;
	hspi3.Init.Mode = SPI_MODE_MASTER;
	hspi3.Init.Direction = SPI_DIRECTION_2LINES;
	hspi3.Init.DataSize = SPI_DATASIZE_16BIT;
	hspi3.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi3.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi3.Init.NSS = SPI_NSS_SOFT;
	hspi3.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
	hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi3.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi3.Init.CRCPolynomial = 10;

	if (HAL_SPI_Init(&hspi3) != HAL_OK)
	{
		Error_Handler();
	}
#else
	hspi3.Instance->CR2 |= SPI_DATASIZE_16BIT; // Set 16 bit mode
	__HAL_SPI_ENABLE(&hspi3);
#endif
	if (HAL_SPI_Receive(&hspi3, num, 1, 1000) != HAL_OK) {
		Error_Handler();
	}
#if 0
	HAL_SPI_DeInit(&hspi3);
#else
	__HAL_SPI_DISABLE(&hspi3);
#endif
	T_CS_ON;

	ret = num[0] << 8 | num[1];
	ret >>= 3;
	ret &= (1<<12)-1;

	return ret;
}

uint16_t XPT2046_Read_XOY(uint8_t xy)
{
	uint16_t i, j;
	uint16_t buf[READ_TIMES];
	uint16_t sum = 0;
	uint16_t temp;
	for(i=0;i<READ_TIMES;i++) buf[i] = XPT2046_Read_AD(xy);
	for(i=0;i<READ_TIMES-1; i++)
	{
		for(j = i+1; j < READ_TIMES; j++)
		{
			if(buf[i] > buf[j])
			{
				temp = buf[i];
				buf[i] = buf[j];
				buf[j] = temp;
			}
		}
	}
	sum = 0;
	for(i = LOST_VAL; i < READ_TIMES - LOST_VAL; i++) sum += buf[i];
	temp = sum / (READ_TIMES - 2 * LOST_VAL);
	return temp;
}

static uint8_t XPT2046_Read_XY(uint16_t *x, uint16_t *y)
{
	uint16_t xtemp,ytemp;
	xtemp = XPT2046_Read_XOY(CMD_RDX);
	ytemp = XPT2046_Read_XOY(CMD_RDY);

	*x = xtemp;
	*y = ytemp;
	return 1;
}

static uint8_t XPT2046_Read_XY2(uint16_t *x, uint16_t *y)
{
	uint16_t x1,y1;
 	uint16_t x2,y2;
 	uint8_t flag;
    flag = XPT2046_Read_XY(&x1 ,&y1);
    if(flag == 0) {
    	return 0;
    }
    flag = XPT2046_Read_XY(&x2, &y2);
    if(flag == 0) {
    	return 0;
    }
    if(((x2 <= x1 && x1 < x2 + ERR_RANGE) || (x1 <= x2 && x2 < x1 + ERR_RANGE))
    && ((y2 <= y1 && y1 < y2 + ERR_RANGE) || (y1 <= y2 && y2 < y1 + ERR_RANGE))) {
        *x = (x1 + x2) / 2;
        *y = (y1 + y2) / 2;
        return 1;
    } else {
    	return 0;
    }
}

uint8_t XPT2046_Scan(void)
{
	if (T_IRQ == GPIO_PIN_RESET) {
		if (XPT2046_Read_XY2(&x, &y) != 0) {
			x = y = 0;
		}
		if ((status & TP_PRES_DOWN) == 0) {
			status = TP_PRES_DOWN | TP_CATH_PRES;
			x0 = x;
			y0 = y;
		}
	} else {
		if (status & TP_PRES_DOWN) {
			status &= ~TP_PRES_DOWN;
		} else {
			x0 = y0 = 0;
			x = y = 0xffff;
		}
	}
	return status & TP_PRES_DOWN;
}

uint8_t XPT2046_GetStatus(void)
{
	return status;
}
