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
// I refer to http://www.lcdwiki.com/2.8inch_SPI_Module_ILI9341_SKU:MSP2807

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

static SPI_HandleTypeDef *lcd_hspi;
static LCD_Window_t lcd_window;

static void LCD_WR_REG(uint8_t data);
static void LCD_WR_DATA(uint8_t data);
static void LCD_direction(LCD_Horizontal_t direction);
static void RESET_L(void);
static void RESET_H(void);
static void CS_L(void);
static void CS_H(void);
static void DC_L(void);
static void DC_H(void);
static void LED_L(void);
static void LED_H(void);

// Initialization
void ILI9341_Init(SPI_HandleTypeDef *hspi)
{
	lcd_hspi = hspi;
	RESET_L();
	HAL_Delay(100);
	RESET_H();
	HAL_Delay(50);

	LCD_WR_REG(0xCF);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0xC9); //C1
	LCD_WR_DATA(0X30);
	LCD_WR_REG(0xED);
	LCD_WR_DATA(0x64);
	LCD_WR_DATA(0x03);
	LCD_WR_DATA(0X12);
	LCD_WR_DATA(0X81);
	LCD_WR_REG(0xE8);
	LCD_WR_DATA(0x85);
	LCD_WR_DATA(0x10);
	LCD_WR_DATA(0x7A);
	LCD_WR_REG(0xCB);
	LCD_WR_DATA(0x39);
	LCD_WR_DATA(0x2C);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x34);
	LCD_WR_DATA(0x02);
	LCD_WR_REG(0xF7);
	LCD_WR_DATA(0x20);
	LCD_WR_REG(0xEA);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);
	LCD_WR_REG(0xC0);    //Power control
	LCD_WR_DATA(0x1B);   //VRH[5:0]
	LCD_WR_REG(0xC1);    //Power control
	LCD_WR_DATA(0x00);   //SAP[2:0];BT[3:0] 01
	LCD_WR_REG(0xC5);    //VCM control
	LCD_WR_DATA(0x30); 	 //3F
	LCD_WR_DATA(0x30); 	 //3C
	LCD_WR_REG(0xC7);    //VCM control2
	LCD_WR_DATA(0XB7);
	LCD_WR_REG(0x36);    // Memory Access Control
	LCD_WR_DATA(0x08);
	LCD_WR_REG(0x3A);
	LCD_WR_DATA(0x55);
	LCD_WR_REG(0xB1);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x1A);
	LCD_WR_REG(0xB6);    // Display Function Control
	LCD_WR_DATA(0x0A);
	LCD_WR_DATA(0xA2);
	LCD_WR_REG(0xF2);    // 3Gamma Function Disable
	LCD_WR_DATA(0x00);
	LCD_WR_REG(0x26);    //Gamma curve selected
	LCD_WR_DATA(0x01);
	LCD_WR_REG(0xE0);    //Set Gamma
	LCD_WR_DATA(0x0F);
	LCD_WR_DATA(0x2A);
	LCD_WR_DATA(0x28);
	LCD_WR_DATA(0x08);
	LCD_WR_DATA(0x0E);
	LCD_WR_DATA(0x08);
	LCD_WR_DATA(0x54);
	LCD_WR_DATA(0XA9);
	LCD_WR_DATA(0x43);
	LCD_WR_DATA(0x0A);
	LCD_WR_DATA(0x0F);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);
	LCD_WR_REG(0XE1);    //Set Gamma
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x15);
	LCD_WR_DATA(0x17);
	LCD_WR_DATA(0x07);
	LCD_WR_DATA(0x11);
	LCD_WR_DATA(0x06);
	LCD_WR_DATA(0x2B);
	LCD_WR_DATA(0x56);
	LCD_WR_DATA(0x3C);
	LCD_WR_DATA(0x05);
	LCD_WR_DATA(0x10);
	LCD_WR_DATA(0x0F);
	LCD_WR_DATA(0x3F);
	LCD_WR_DATA(0x3F);
	LCD_WR_DATA(0x0F);
	LCD_WR_REG(0x2B);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x01);
	LCD_WR_DATA(0x3f);
	LCD_WR_REG(0x2A);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0xef);
	LCD_WR_REG(0x11); //Exit Sleep
	HAL_Delay(120);
	LCD_WR_REG(0x29); //display on

	LCD_direction(ROTATE_90);
	LED_H();

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
}

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

	CS_L();
	DC_H();
	for (int i = 0; i < lcd_window.height; i++) {
		HAL_SPI_Transmit(lcd_hspi, data, lcd_window.width*2, 1000);
	}
	CS_H();

}

void ILI9341_WritePixel(uint16_t color)
{
	uint8_t data[2];
	data[0] = color >> 8;
	data[1] = color;
	CS_L();
	DC_H();
	HAL_SPI_Transmit(lcd_hspi, data, 2, 1000);
	CS_H();
}

void ILI9341_Reset(void)
{
	RESET_L();
	HAL_Delay(100);
	RESET_H();
	HAL_Delay(50);
}

void ILI9341_ReadID(uint8_t *data)
{
	uint8_t cmd;
	cmd = 0x04; //Read Display Identification Information
	DC_L();
	CS_L();
	HAL_SPI_Transmit(lcd_hspi, &cmd, 1, 1000);
	CS_H();
	DC_H();
	CS_L();
	HAL_SPI_Receive(lcd_hspi, data, 4, 1000);
	CS_H();
}

void ILI9341_ReadDisplayStatus(uint8_t *data)
{
	uint8_t cmd;
	cmd = 0x09; //Read Display Status
	DC_L();
	CS_L();
	HAL_SPI_Transmit(lcd_hspi, &cmd, 1, 1000);
	CS_H();
	DC_H();
	CS_L();
	HAL_SPI_Receive(lcd_hspi, data, 5, 1000);
	CS_H();
}

static void LCD_WR_REG(uint8_t data)
{
	CS_L();
	DC_L();
	if (HAL_SPI_Transmit(lcd_hspi, &data, 1, 1000) != HAL_OK) {
		Error_Handler();
	}
	CS_H();
}

static void LCD_WR_DATA(uint8_t data)
{
	CS_L();
	DC_H();
	if (HAL_SPI_Transmit(lcd_hspi, &data, 1, 1000) != HAL_OK) {
		Error_Handler();
	}
	CS_H();
}

static void LCD_direction(LCD_Horizontal_t direction)
{
	switch (direction) {
	case ROTATE_0:
		lcd_window.width = 240;
		lcd_window.height = 320;
		LCD_WR_REG(0x36);
		LCD_WR_DATA((1<<3)|(0<<6)|(0<<7));
		break;
	case ROTATE_90:
		lcd_window.width = 320;
		lcd_window.height = 240;
		LCD_WR_REG(0x36);
		LCD_WR_DATA((1<<3)|(0<<7)|(1<<6)|(1<<5));
		break;
	case ROTATE_180:
		lcd_window.width = 240;
		lcd_window.height = 320;
		LCD_WR_REG(0x36);
		LCD_WR_DATA((1<<3)|(1<<6)|(1<<7));
	case ROTATE_270:
		lcd_window.width = 320;
		lcd_window.height = 240;
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

static void CS_H(void)
{
	HAL_GPIO_WritePin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin, GPIO_PIN_SET);
}

static void DC_L(void)
{
	HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_RESET);
}

static void DC_H(void)
{
	HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_SET);
}

static void LED_L(void)
{
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
}

static void LED_H(void)
{
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
}

