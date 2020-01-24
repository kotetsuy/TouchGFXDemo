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
  QSPI_CommandTypeDef     sCommand = {0};
  QSPI_AutoPollingTypeDef sConfig = {0};
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
	QSPI_CommandTypeDef     sCommand = {0};
	QSPI_AutoPollingTypeDef sConfig = {0};
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
	//QSPI_AutoPollingTypeDef sConfig = {0};
	uint8_t reg;
	HAL_StatusTypeDef ret;

	if (State != W25Q128JV_INIT) {
		return HAL_ERROR;
	}
	State = W25Q128JV_BUSY;

	/* Enable Reset --------------------------- */
	sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
	sCommand.Instruction       = ENABLE_RESET;
	sCommand.AddressMode       = QSPI_ADDRESS_NONE;
	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode          = QSPI_DATA_NONE;
	sCommand.DummyCycles       = 0;
	sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

	if ((ret = HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)) != HAL_OK)
	{
    	State = W25Q128JV_OK;
		return ret;
	}

	/* Reset Device --------------------------- */
	sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
	sCommand.Instruction       = RESET_DEVICE;
	sCommand.AddressMode       = QSPI_ADDRESS_NONE;
	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode          = QSPI_DATA_NONE;
	sCommand.DummyCycles       = 0;
	sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

	if ((ret = HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)) != HAL_OK)
	{
    	State = W25Q128JV_OK;
		return ret;
	}

	HAL_Delay(100);

	/* Read Volatile Configuration register 2 --------------------------- */
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

#if 0
	/* Enable write operations ------------------------------------------- */
	if ((ret = QSPI_WriteEnable(&hqspi)) != HAL_OK) {
    	State = W25Q128JV_OK;
		return ret;
	}
#endif
	/* Enable Volatile Write operations ---------------------------------------- */
	sCommand.DataMode          = QSPI_DATA_NONE;
	sCommand.Instruction = VOLATILE_SR_WRITE_ENABLE;

	if (HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
    	State = W25Q128JV_OK;
		return ret;
	}

	/* Write Volatile Configuration register 2 (QE = 1) -- */
	sCommand.DataMode          = QSPI_DATA_1_LINE;
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

	/* Read Volatile Configuration register 3 --------------------------- */
	sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
	sCommand.Instruction       = READ_STATUS_REG3_CMD;
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

	/* Write Volatile Configuration register 2 (DRV1:2 = 00) -- */
	sCommand.Instruction = WRITE_STATUS_REG3_CMD;
	reg &= 0x9f; // DRV1:2 bit

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

#if 0
	/* Configure automatic polling mode to wait for memory ready ------ */
	sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
	sCommand.Instruction       = READ_STATUS_REG2_CMD;
	sCommand.AddressMode       = QSPI_ADDRESS_NONE;
	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode          = QSPI_DATA_1_LINE;
	sCommand.DummyCycles       = 0;
	sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

	sConfig.Match           = 0x02;
	sConfig.Mask            = 0x02;
	sConfig.MatchMode       = QSPI_MATCH_MODE_AND;
	sConfig.StatusBytesSize = 1;
	sConfig.Interval        = 0x10;
	sConfig.AutomaticStop   = QSPI_AUTOMATIC_STOP_ENABLE;

	if ((ret = HAL_QSPI_AutoPolling(&hqspi, &sCommand, &sConfig, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)) != HAL_OK)
	{
		return ret;
	}
#endif
	State = W25Q128JV_OK;
	return HAL_OK;
}

// Blocked function
// flash_address is boundary 0x10000
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

    if ((ret = HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)) != HAL_OK)
    {
    	State = W25Q128JV_OK;
    	return ret;
    }
	State = W25Q128JV_OK;
    return HAL_OK;
}

// Blocked function
// flash_address is boundary 256
// max l is 256
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
	if (l > 256) {
		return HAL_ERROR;
	}
	if ((flash_address & 0xff) != 0) {
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
    if ((ret = HAL_QSPI_Transmit(&hqspi, s, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)) != HAL_OK)
    {
    	State = W25Q128JV_OK;
		return ret;
    }
	State = W25Q128JV_OK;
	return HAL_OK;
}

// Blocked function
// flash_address is boundary 16
// max l is 16
HAL_StatusTypeDef W25Q128JV_ReadQuad(uint32_t flash_address, uint8_t *d, int32_t l)
{
	QSPI_CommandTypeDef     sCommand = {0};
	HAL_StatusTypeDef ret;

	if (State == W25Q128JV_BUSY) {
		return HAL_BUSY;
	}
	if (State == W25Q128JV_INIT) {
		return HAL_ERROR;
	}
#if 0
	if (l > 16) {
		return HAL_ERROR;
	}
	if ((flash_address & 0xf) != 0) {
		return HAL_ERROR;
	}
#endif
	State = W25Q128JV_BUSY;

	sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
	sCommand.AddressSize       = QSPI_ADDRESS_24_BITS;
	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;
    sCommand.Instruction = FAST_READ_QUAD_OUTPUT;
    sCommand.DummyCycles = 8;
    sCommand.Address     = flash_address;
    sCommand.AddressMode = QSPI_ADDRESS_1_LINE;
    sCommand.DataMode    = QSPI_DATA_4_LINES;
    sCommand.NbData      = l;

    if ((ret = HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)) != HAL_OK)
    {
    	State = W25Q128JV_OK;
		return ret;
    }
    if ((ret = HAL_QSPI_Receive(&hqspi, d, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)) != HAL_OK)
    {
    	State = W25Q128JV_OK;
		return ret;
    }
	State = W25Q128JV_OK;
	return HAL_OK;
}

// Blocked function
// flash_address is boundary 16
// max l is 16
HAL_StatusTypeDef W25Q128JV_Read1Line(uint32_t flash_address, uint8_t *d, int32_t l)
{
	QSPI_CommandTypeDef     sCommand = {0};
	HAL_StatusTypeDef ret;

	if (State == W25Q128JV_BUSY) {
		return HAL_BUSY;
	}
	if (State == W25Q128JV_INIT) {
		return HAL_ERROR;
	}
#if 0
	if (l > 16) {
		return HAL_ERROR;
	}
	if ((flash_address & 0xf) != 0) {
		return HAL_ERROR;
	}
#endif
	State = W25Q128JV_BUSY;

	sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
	sCommand.AddressSize       = QSPI_ADDRESS_24_BITS;
	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;
    sCommand.Instruction = READ_DATA_CMD;
    sCommand.DummyCycles = 0;
    sCommand.Address     = flash_address;
    sCommand.AddressMode = QSPI_ADDRESS_1_LINE;
    sCommand.DataMode    = QSPI_DATA_1_LINE;
    sCommand.NbData      = l;

    if ((ret = HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)) != HAL_OK)
    {
    	State = W25Q128JV_OK;
		return ret;
    }
    if ((ret = HAL_QSPI_Receive(&hqspi, d, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)) != HAL_OK)
    {
    	State = W25Q128JV_OK;
		return ret;
    }
	State = W25Q128JV_OK;
	return HAL_OK;
}

// Blocked function
// flash_address is boundary 16
// max l is 16
HAL_StatusTypeDef W25Q128JV_ReadFast1Line(uint32_t flash_address, uint8_t *d, int32_t l)
{
	QSPI_CommandTypeDef     sCommand = {0};
	HAL_StatusTypeDef ret;

	if (State == W25Q128JV_BUSY) {
		return HAL_BUSY;
	}
	if (State == W25Q128JV_INIT) {
		return HAL_ERROR;
	}
	if (l > 65535) {
		return HAL_ERROR;
	}
	State = W25Q128JV_BUSY;

	sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
	sCommand.AddressSize       = QSPI_ADDRESS_24_BITS;
	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;
    sCommand.Instruction = FAST_READ_DATA_CMD;
    sCommand.DummyCycles = 8;
    sCommand.Address     = flash_address;
    sCommand.AddressMode = QSPI_ADDRESS_1_LINE;
    sCommand.DataMode    = QSPI_DATA_1_LINE;
    sCommand.NbData      = l;

    if ((ret = HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)) != HAL_OK)
    {
    	State = W25Q128JV_OK;
		return ret;
    }
    if ((ret = HAL_QSPI_Receive(&hqspi, d, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)) != HAL_OK)
    {
    	State = W25Q128JV_OK;
		return ret;
    }
	State = W25Q128JV_OK;
	return HAL_OK;
}

// Blocked function
// flash_address is boundary 16
// max l is 16
HAL_StatusTypeDef W25Q128JV_ReadDual(uint32_t flash_address, uint8_t *d, int32_t l)
{
	QSPI_CommandTypeDef     sCommand = {0};
	HAL_StatusTypeDef ret;

	if (State == W25Q128JV_BUSY) {
		return HAL_BUSY;
	}
	if (State == W25Q128JV_INIT) {
		return HAL_ERROR;
	}
#if 0
	if (l > 16) {
		return HAL_ERROR;
	}
	if ((flash_address & 0xf) != 0) {
		return HAL_ERROR;
	}
#endif
	State = W25Q128JV_BUSY;

	sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
	sCommand.AddressSize       = QSPI_ADDRESS_24_BITS;
	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;
    sCommand.Instruction = FAST_READ_DUAL_OUTPUT;
    sCommand.DummyCycles = 8;
    sCommand.Address     = flash_address;
    sCommand.AddressMode = QSPI_ADDRESS_1_LINE;
    sCommand.DataMode    = QSPI_DATA_2_LINES;
    sCommand.NbData      = l;

    if ((ret = HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)) != HAL_OK)
    {
    	State = W25Q128JV_OK;
		return ret;
    }
    if ((ret = HAL_QSPI_Receive(&hqspi, d, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)) != HAL_OK)
    {
    	State = W25Q128JV_OK;
		return ret;
    }
	State = W25Q128JV_OK;
	return HAL_OK;
}

HAL_StatusTypeDef W25Q128JV_MemoryMapped(void)
{
	QSPI_CommandTypeDef     sCommand = {0};
	QSPI_MemoryMappedTypeDef sMemMappedCfg = {0};
	HAL_StatusTypeDef ret;

	sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
	sCommand.AddressSize       = QSPI_ADDRESS_24_BITS;
	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;
    sCommand.Instruction = FAST_READ_DUAL_OUTPUT;
    sCommand.DummyCycles = 8;
    sCommand.Address     = 0;
    sCommand.AddressMode = QSPI_ADDRESS_1_LINE;
    sCommand.DataMode    = QSPI_DATA_2_LINES;
    sCommand.NbData      = 16*1024*1024;

    sMemMappedCfg.TimeOutActivation = QSPI_TIMEOUT_COUNTER_DISABLE;

    if ((ret = HAL_QSPI_MemoryMapped(&hqspi, &sCommand, &sMemMappedCfg)) != HAL_OK)
    {
		return ret;
    }
	return HAL_OK;
}

