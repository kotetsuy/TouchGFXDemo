/*
 * ili9341.c
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

#include <ili9341.h>
#include "main.h" // Hardware setting

// This function is for compatible HiLetgo ILI9341

typedef enum {
	ROTATE_0,
	ROTATE_90,
	ROTATE_180,
	ROTATE_270
} LCD_Horizontal_t;

typedef struct {
	uint16_t width;
	uint16_t height;
} LCD_Window_t;

extern void Error_Handler(void);
extern SPI_HandleTypeDef hspi1;

//static LCD_Window_t lcd_window;

void ILI9341_Reset(void);
void ILI9341_SoftReset(void);

static void LCD_WR_REG(uint8_t data);
static void LCD_WR_DATA(uint8_t data);
static void LCD_direction(LCD_Horizontal_t direction);
static void RESET_L(void);
static void RESET_H(void);
static void CS_L(void);
//static void CS_H(void);
static void DC_L(void);
static void DC_H(void);
//static void LED_L(void);
static void LED_H(void);

// Initialization
void ILI9341_Init(void)
{
	ILI9341_Reset();
	ILI9341_SoftReset();

	// I refer https://github.com/dtnghia2206/TFTLCD/blob/master/TFTLCD/ILI9341/ILI9341_Driver.c
	/* Power Control A */
	LCD_WR_REG(0xCB);
	LCD_WR_DATA(0x39);
	LCD_WR_DATA(0x2C);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x34);
	LCD_WR_DATA(0x02);
	/* Power Control B */
	LCD_WR_REG(0xCF);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0xC1);
	LCD_WR_DATA(0x30);
	/* Driver timing control A */
	LCD_WR_REG(0xE8);
	LCD_WR_DATA(0x85);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x78);
	/* Driver timing control B */
	LCD_WR_REG(0xEA);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);
	/* Power on Sequence control */
	LCD_WR_REG(0xED);
	LCD_WR_DATA(0x64);
	LCD_WR_DATA(0x03);
	LCD_WR_DATA(0x12);
	LCD_WR_DATA(0x81);
	/* Pump ratio control */
	LCD_WR_REG(0xF7);
	LCD_WR_DATA(0x20);
	/* Power Control 1 */
	LCD_WR_REG(0xC0);
	LCD_WR_DATA(0x10);
	/* Power Control 2 */
	LCD_WR_REG(0xC1);
	LCD_WR_DATA(0x10);
	/* VCOM Control 1 */
	LCD_WR_REG(0xC5);
	LCD_WR_DATA(0x3E);
	LCD_WR_DATA(0x28);
	/* VCOM Control 2 */
	LCD_WR_REG(0xC7);
	LCD_WR_DATA(0x86);
	/* VCOM Control 2 */
	LCD_WR_REG(0x36);
	LCD_WR_DATA(0x48);
	/* Pixel Format Set */
	LCD_WR_REG(0x3A);
	LCD_WR_DATA(0x55);    //16bit
	LCD_WR_REG(0xB1);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x18);
	/* Display Function Control */
	LCD_WR_REG(0xB6);
	LCD_WR_DATA(0x08);
	LCD_WR_DATA(0x82);
	LCD_WR_DATA(0x27);
	/* 3GAMMA FUNCTION DISABLE */
	LCD_WR_REG(0xF2);
	LCD_WR_DATA(0x00);
	/* GAMMA CURVE SELECTED */
	LCD_WR_REG(0x26); //Gamma set
	LCD_WR_DATA(0x01); 	//Gamma Curve (G2.2)
	//Positive Gamma  Correction
	LCD_WR_REG(0xE0);
	LCD_WR_DATA(0x0F);
	LCD_WR_DATA(0x31);
	LCD_WR_DATA(0x2B);
	LCD_WR_DATA(0x0C);
	LCD_WR_DATA(0x0E);
	LCD_WR_DATA(0x08);
	LCD_WR_DATA(0x4E);
	LCD_WR_DATA(0xF1);
	LCD_WR_DATA(0x37);
	LCD_WR_DATA(0x07);
	LCD_WR_DATA(0x10);
	LCD_WR_DATA(0x03);
	LCD_WR_DATA(0x0E);
	LCD_WR_DATA(0x09);
	LCD_WR_DATA(0x00);
	//Negative Gamma  Correction
	LCD_WR_REG(0xE1);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x0E);
	LCD_WR_DATA(0x14);
	LCD_WR_DATA(0x03);
	LCD_WR_DATA(0x11);
	LCD_WR_DATA(0x07);
	LCD_WR_DATA(0x31);
	LCD_WR_DATA(0xC1);
	LCD_WR_DATA(0x48);
	LCD_WR_DATA(0x08);
	LCD_WR_DATA(0x0F);
	LCD_WR_DATA(0x0C);
	LCD_WR_DATA(0x31);
	LCD_WR_DATA(0x36);
	LCD_WR_DATA(0x0F);
	//EXIT SLEEP
	LCD_WR_REG(0x11);

	HAL_Delay(120);

	//TURN ON DISPLAY
	LCD_WR_REG(0x29);
	LCD_WR_DATA(0x2C);

	LCD_direction(ROTATE_90);
}

void ILI9341_SetWindow(uint16_t start_x, uint16_t start_y, uint16_t end_x, uint16_t end_y)
{
	// Set Window
	LCD_WR_REG(0x2a);
	LCD_WR_DATA(start_x >> 8);
	LCD_WR_DATA(0xFF & start_x);
	LCD_WR_DATA(end_x >> 8);
	LCD_WR_DATA(0xFF & end_x);

	LCD_WR_REG(0x2b);
	LCD_WR_DATA(start_y >> 8);
	LCD_WR_DATA(0xFF & start_y);
	LCD_WR_DATA(end_y >> 8);
	LCD_WR_DATA(0xFF & end_y);

	//lcd_window.width = end_x - start_x + 1;
	//lcd_window.height = end_x - start_x + 1;
}

void ILI9341_WritePixel(uint16_t x, uint16_t y, uint16_t color)
{
	uint8_t data[2];
	data[0] = color >> 8;
	data[1] = color;
	ILI9341_SetWindow(x, x+1, y, y+1);
	DC_H();
	if (HAL_SPI_Transmit(&hspi1, data, 2, 1000) != HAL_OK) {
		Error_Handler();
	}
}

// Call this function after ILI9341_SetWindow
// This function is non blocked
// The variable for Callback is open. User should set by himself
void ILI9341_DrawBitmap(uint16_t w, uint16_t h, uint8_t *s)
{
	// Enable to access GRAM
	LCD_WR_REG(0x2c);

	DC_H();
	HAL_SPI_Transmit_DMA(&hspi1, (uint8_t*)s, w * h *sizeof(uint16_t));
}

#if 0
void ILI9341_Fill(uint16_t color)
{
	uint8_t data[320*2];

	// Prepare line data
	for (int i = 0; i < lcd_window.width*2;){
		data[i++] = color >> 8;
		data[i++] = color;
	}

	ILI9341_SetWindow(0, 0, lcd_window.width-1, lcd_window.height-1);

	// Enable to access GRAM
	LCD_WR_REG(0x2c);

	//CS_L();
	DC_H();
	for (int i = 0; i < lcd_window.height; i++) {
		HAL_SPI_Transmit(&hspi1, data, lcd_window.width*2, 1000);
	}
	//CS_H();

}

#endif

void ILI9341_Reset(void)
{
	RESET_L();
	HAL_Delay(100);
	RESET_H();
	HAL_Delay(100);
	CS_L();
	LED_H();
}

void ILI9341_SoftReset(void)
{
	uint8_t cmd;
	cmd = 0x01; //Software reset
	DC_L();
	if (HAL_SPI_Transmit(&hspi1, &cmd, 1, 1000) != HAL_OK) {
		Error_Handler();
	}
}


static void LCD_WR_REG(uint8_t data)
{
	//CS_L();
	DC_L();
	if (HAL_SPI_Transmit(&hspi1, &data, 1, 1000) != HAL_OK) {
		Error_Handler();
	}
	//CS_H();
}

static void LCD_WR_DATA(uint8_t data)
{
	//CS_L();
	DC_H();
	if (HAL_SPI_Transmit(&hspi1, &data, 1, 1000) != HAL_OK) {
		Error_Handler();
	}
	//CS_H();
}

static void LCD_direction(LCD_Horizontal_t direction)
{
	switch (direction) {
	case ROTATE_0:
		LCD_WR_REG(0x36);
		LCD_WR_DATA((1<<3)|(0<<6)|(0<<7));
		break;
	case ROTATE_90:
		LCD_WR_REG(0x36);
		LCD_WR_DATA((1<<3)|(0<<7)|(1<<6)|(1<<5));
		break;
	case ROTATE_180:
		LCD_WR_REG(0x36);
		LCD_WR_DATA((1<<3)|(1<<6)|(1<<7));
	case ROTATE_270:
		LCD_WR_REG(0x36);
		LCD_WR_DATA((1<<3)|(1<<7)|(1<<5));
		break;
	}
}

static void RESET_L(void)
{
	HAL_GPIO_WritePin(RESET_GPIO_Port, RESET_Pin, GPIO_PIN_RESET);
}

static void RESET_H(void)
{
	HAL_GPIO_WritePin(RESET_GPIO_Port, RESET_Pin, GPIO_PIN_SET);
}

static void CS_L(void)
{
	HAL_GPIO_WritePin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin, GPIO_PIN_RESET);
}

#if 0
static void CS_H(void)
{
	HAL_GPIO_WritePin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin, GPIO_PIN_SET);
}
#endif

static void DC_L(void)
{
	HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_RESET);
}

static void DC_H(void)
{
	HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_SET);
}

#if 0
static void LED_L(void)
{
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
}
#endif

static void LED_H(void)
{
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
}

