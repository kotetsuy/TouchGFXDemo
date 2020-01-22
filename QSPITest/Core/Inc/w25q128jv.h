/*
 * w25128jv.h
 *
 *  Created on: Jan 22, 2020
 *      Author: Kotetsu Yamamoto
 *      Copyright [Kotetsu Yamamoto]
 *
MIT License

Copyright (c) 2020 Kotetsu Yamamoto

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
 *
 */

#ifndef INC_W25Q128JV_H_
#define INC_W25Q128JV_H_

typedef enum {
	W25Q128JV_INIT,
	W25Q128JV_OK,
	W25Q128JV_BUSY
} W25Q128JV_State_t;

/* Read Operations */
#define QUAD_INOUT_FAST_READ_CMD             0xEB //

/* Write Operations */
#define WRITE_ENABLE_CMD                     0x06 //

/* Register Operations */
#define READ_STATUS_REG_CMD                  0x05 //
#define READ_STATUS_REG2_CMD                 0x35 //
#define WRITE_STATUS_REG2_CMD                0x31 //

/* Program Operations */
#define PAGE_PROG_CMD                        0x02 //

/* Erase Operations */
#define BLOCK_ERASE_CMD                      0xD8 // 64Kbyte block erase

#define DUMMY_CLOCK_CYCLES_READ_QUAD         4 //

HAL_StatusTypeDef W25Q128JV_AutoPollingMemReady(QSPI_HandleTypeDef *hqspi);
HAL_StatusTypeDef W25Q128JV_Init(void);
HAL_StatusTypeDef W25Q128JV_EraseBlock(uint32_t flash_address);
HAL_StatusTypeDef W25Q128JV_Write(uint32_t flash_address, uint8_t *s, int32_t l);
HAL_StatusTypeDef W25Q128JV_Read(uint32_t flash_address, uint8_t *d, int32_t l);
W25Q128JV_State_t W25Q128JV_IsBusy(void);


#endif /* INC_W25Q128JV_H_ */
