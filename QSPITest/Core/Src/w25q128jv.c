/*
 * w25128jv.c
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
#include "main.h" // For hardware
#include "w25q128jv.h"

extern QSPI_HandleTypeDef hqspi; // from main.c

static W25Q128JV_State_t State = W25Q128JV_INIT;
static __IO uint8_t CmdCplt, TxCplt, RxCplt;

/**
  * @brief  This function send a Write Enable and wait it is effective.
  * @param  hqspi: QSPI handle
  * @retval None
  */
static HAL_StatusTypeDef QSPI_WriteEnable(QSPI_HandleTypeDef *hqspi)
{
  QSPI_CommandTypeDef     sCommand;
  QSPI_AutoPollingTypeDef sConfig;
  HAL_StatusTypeDef ret;

  /* Enable write operations ------------------------------------------ */
  sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
  sCommand.Instruction       = WRITE_ENABLE_CMD;
  sCommand.AddressMode       = QSPI_ADDRESS_NONE;
  sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  sCommand.DataMode          = QSPI_DATA_NONE;
  sCommand.DummyCycles       = 0;
  sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;
  sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
  sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

  if ((ret = HAL_QSPI_Command(hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)) != HAL_OK)
  {
    return ret;
  }

  /* Configure automatic polling mode to wait for write enabling ---- */
  sConfig.Match           = 0x02;
  sConfig.Mask            = 0x02;
  sConfig.MatchMode       = QSPI_MATCH_MODE_AND;
  sConfig.StatusBytesSize = 1;
  sConfig.Interval        = 0x10;
  sConfig.AutomaticStop   = QSPI_AUTOMATIC_STOP_ENABLE;

  sCommand.Instruction    = READ_STATUS_REG_CMD;
  sCommand.DataMode       = QSPI_DATA_1_LINE;

  if ((ret = HAL_QSPI_AutoPolling(hqspi, &sCommand, &sConfig, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)) != HAL_OK)
  {
    return ret;
  }
  return HAL_OK;
}

// Blocked function
HAL_StatusTypeDef W25Q128JV_AutoPollingMemReady(QSPI_HandleTypeDef *hqspi)
{
	QSPI_CommandTypeDef     sCommand;
	QSPI_AutoPollingTypeDef sConfig;
	HAL_StatusTypeDef ret;

	if (State == W25Q128JV_BUSY) {
		return HAL_BUSY;
	}
	if (State == W25Q128JV_INIT) {
		return HAL_ERROR;
	}
	State = W25Q128JV_BUSY;

	/* Configure automatic polling mode to wait for memory ready ------ */
	sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
	sCommand.Instruction       = READ_STATUS_REG_CMD;
	sCommand.AddressMode       = QSPI_ADDRESS_NONE;
	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode          = QSPI_DATA_1_LINE;
	sCommand.DummyCycles       = 0;
	sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

	sConfig.Match           = 0x00;
	sConfig.Mask            = 0x01;
	sConfig.MatchMode       = QSPI_MATCH_MODE_AND;
	sConfig.StatusBytesSize = 1;
	sConfig.Interval        = 0x10;
	sConfig.AutomaticStop   = QSPI_AUTOMATIC_STOP_ENABLE;

	if ((ret = HAL_QSPI_AutoPolling(hqspi, &sCommand, &sConfig, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)) != HAL_OK)
	{
		return ret;
	}
	State = W25Q128JV_OK;
	return HAL_OK;
}

// Blocked function
HAL_StatusTypeDef W25Q128JV_Init(void)
{
	QSPI_CommandTypeDef     sCommand = {0};
	uint8_t reg;
	HAL_StatusTypeDef ret;

	if (State != W25Q128JV_INIT) {
		return HAL_ERROR;
	}
	State = W25Q128JV_BUSY;

	/* Read Volatile Configuration register --------------------------- */
	sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
	sCommand.Instruction       = READ_STATUS_REG2_CMD;
	sCommand.AddressMode       = QSPI_ADDRESS_NONE;
	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode          = QSPI_DATA_1_LINE;
	sCommand.DummyCycles       = 0;
	sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;
	sCommand.NbData            = 1;

	if ((ret = HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)) != HAL_OK)
	{
    	State = W25Q128JV_OK;
		return ret;
	}

	if ((ret = HAL_QSPI_Receive(&hqspi, &reg, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)) != HAL_OK)
	{
    	State = W25Q128JV_OK;
		return ret;
	}

	/* Enable write operations ---------------------------------------- */
	QSPI_WriteEnable(&hqspi);

	/* Write Volatile Configuration register (QE = 1) -- */
	sCommand.Instruction = WRITE_STATUS_REG2_CMD;
	reg |= 2; // QE bit

	if (HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
    	State = W25Q128JV_OK;
		return ret;
	}

	if (HAL_QSPI_Transmit(&hqspi, &reg, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
    	State = W25Q128JV_OK;
		return ret;
	}

	State = W25Q128JV_OK;
	return HAL_OK;
}

// Blocked function
HAL_StatusTypeDef W25Q128JV_EraseBlock(uint32_t flash_address)
{
	QSPI_CommandTypeDef     sCommand = {0};
	HAL_StatusTypeDef ret;

	if (State == W25Q128JV_BUSY) {
		return HAL_BUSY;
	}
	if (State == W25Q128JV_INIT) {
		return HAL_ERROR;
	}
	if ((flash_address & 0xffff) != 0) {
		return HAL_ERROR;
	}
	State = W25Q128JV_BUSY;

	sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
	sCommand.AddressSize       = QSPI_ADDRESS_24_BITS;
	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

    /* Enable write operations ------------------------------------------- */
	if ((ret = QSPI_WriteEnable(&hqspi)) != HAL_OK) {
    	State = W25Q128JV_OK;
		return ret;
	}

    /* Erasing Sequence -------------------------------------------------- */
    sCommand.Instruction = BLOCK_ERASE_CMD;
    sCommand.AddressMode = QSPI_ADDRESS_1_LINE;
    sCommand.Address     = flash_address;
    sCommand.DataMode    = QSPI_DATA_NONE;
    sCommand.DummyCycles = 0;

    CmdCplt = 0;
    if ((ret = HAL_QSPI_Command_IT(&hqspi, &sCommand)) != HAL_OK)
    {
    	State = W25Q128JV_OK;
    	return ret;
    }
    while (CmdCplt == 0)
    	;
	State = W25Q128JV_OK;
    return HAL_OK;
}

// Blocked function
HAL_StatusTypeDef W25Q128JV_Write(uint32_t flash_address, uint8_t *s, int32_t l)
{
	QSPI_CommandTypeDef     sCommand = {0};
	HAL_StatusTypeDef ret;

	if (State == W25Q128JV_BUSY) {
		return HAL_BUSY;
	}
	if (State == W25Q128JV_INIT) {
		return HAL_ERROR;
	}
	State = W25Q128JV_BUSY;
	if (l > 256) {
		return HAL_ERROR;
	}
	if ((flash_address & 0xff) != 0) {
		return HAL_ERROR;
	}

	sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
	sCommand.AddressSize       = QSPI_ADDRESS_24_BITS;
	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

    /* Enable write operations ------------------------------------------- */
	if ((ret = QSPI_WriteEnable(&hqspi)) != HAL_OK) {
    	State = W25Q128JV_OK;
		return ret;
	}

    /* Writing Sequence ------------------------------------------------ */
    sCommand.Instruction = PAGE_PROG_CMD;
    sCommand.AddressMode = QSPI_ADDRESS_1_LINE;
    sCommand.Address     = flash_address;
    sCommand.DataMode    = QSPI_DATA_1_LINE;
    sCommand.NbData      = l;

    if ((ret = HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)) != HAL_OK)
    {
    	State = W25Q128JV_OK;
		return ret;
    }
    TxCplt = 0;
    if ((ret = HAL_QSPI_Transmit_IT(&hqspi, s)) != HAL_OK)
    {
    	State = W25Q128JV_OK;
		return ret;
    }
    while (TxCplt == 0)
    	;
	State = W25Q128JV_OK;
	return HAL_OK;
}

// Blocked function
HAL_StatusTypeDef W25Q128JV_Read(uint32_t flash_address, uint8_t *d, int32_t l)
{
	QSPI_CommandTypeDef     sCommand = {0};
	HAL_StatusTypeDef ret;

	if (State == W25Q128JV_BUSY) {
		return HAL_BUSY;
	}
	if (State == W25Q128JV_INIT) {
		return HAL_ERROR;
	}
	State = W25Q128JV_BUSY;

	sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
	sCommand.AddressSize       = QSPI_ADDRESS_24_BITS;
	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;
    sCommand.Instruction = QUAD_INOUT_FAST_READ_CMD;
    sCommand.DummyCycles = DUMMY_CLOCK_CYCLES_READ_QUAD;
    sCommand.Address     = flash_address;
    sCommand.AddressMode = QSPI_ADDRESS_4_LINES;
    sCommand.DataMode    = QSPI_DATA_4_LINES;
    sCommand.NbData      = l;

    if ((ret = HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)) != HAL_OK)
    {
    	State = W25Q128JV_OK;
		return ret;
    }
    RxCplt = 0;
    if ((ret = HAL_QSPI_Receive_IT(&hqspi, d)) != HAL_OK)
    {
    	State = W25Q128JV_OK;
		return ret;
    }
    while (RxCplt == 0)
    	;
	State = W25Q128JV_OK;
	return HAL_OK;
}

W25Q128JV_State_t W25Q128JV_IsBusy(void)
{
	if (State == W25Q128JV_OK) {
		return 0;
	}
	return 1;
}

/**
  * @brief  Command completed callbacks.
  * @param  hqspi: QSPI handle
  * @retval None
  */
void HAL_QSPI_CmdCpltCallback(QSPI_HandleTypeDef *hqspi)
{
	if (hqspi->Instance == QUADSPI) {
		CmdCplt = 1;
		State = W25Q128JV_OK;
	}
}

/**
  * @brief  Tx Transfer completed callbacks.
  * @param  hqspi: QSPI handle
  * @retval None
  */
void HAL_QSPI_TxCpltCallback(QSPI_HandleTypeDef *hqspi)
{
	if (hqspi->Instance == QUADSPI) {
		TxCplt = 1;
		State = W25Q128JV_OK;
	}
}

/**
  * @brief  Rx Transfer completed callbacks.
  * @param  hqspi: QSPI handle
  * @retval None
  */
void HAL_QSPI_RxCpltCallback(QSPI_HandleTypeDef *hqspi)
{
	if (hqspi->Instance == QUADSPI) {
		RxCplt = 1;
		State = W25Q128JV_OK;
	}
}


