/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "w25q128jv.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
QSPI_HandleTypeDef hqspi;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_QUADSPI_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int main(void)
{
	return 0;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int Init(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_QUADSPI_Init();
  /* USER CODE BEGIN 2 */
  W25Q128JV_Init();

  /* USER CODE END 2 */
 
 

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  return 0;
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief QUADSPI Initialization Function
  * @param None
  * @retval None
  */
static void MX_QUADSPI_Init(void)
{

  /* USER CODE BEGIN QUADSPI_Init 0 */

  /* USER CODE END QUADSPI_Init 0 */

  /* USER CODE BEGIN QUADSPI_Init 1 */

  /* USER CODE END QUADSPI_Init 1 */
  /* QUADSPI parameter configuration*/
  hqspi.Instance = QUADSPI;
  hqspi.Init.ClockPrescaler = 0;
  hqspi.Init.FifoThreshold = 4;
  hqspi.Init.SampleShifting = QSPI_SAMPLE_SHIFTING_HALFCYCLE;
  hqspi.Init.FlashSize = 23;
  hqspi.Init.ChipSelectHighTime = QSPI_CS_HIGH_TIME_6_CYCLE;
  hqspi.Init.ClockMode = QSPI_CLOCK_MODE_0;
  hqspi.Init.FlashID = QSPI_FLASH_ID_1;
  hqspi.Init.DualFlash = QSPI_DUALFLASH_DISABLE;
  if (HAL_QSPI_Init(&hqspi) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN QUADSPI_Init 2 */

  /* USER CODE END QUADSPI_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */
#define QSPI_PAGESIZE 0x100
#define QSPI_FLASHSIZE (16*1024*1024)
#define QSPI_BLOCKSIZE 0x10000
/*******************************************************************************
 Description :
 Write data to the device
 Inputs :
 				Address 	: Write location
 				Size 		: Length in bytes
 				buffer 		: Address where to get the data to write
 outputs :
 				"1" 	        : Operation succeeded
 Info :
 Note : Mandatory for all types except SRAM and PSRAM
********************************************************************************/
int Write (uint32_t Address, uint32_t Size, uint8_t* buffer)
{

  uint32_t NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;
  uint32_t   QSPI_DataNum = 0;

  Addr = Address % QSPI_PAGESIZE;
  count = QSPI_PAGESIZE - Addr;
  NumOfPage =  Size / QSPI_PAGESIZE;
  NumOfSingle = Size % QSPI_PAGESIZE;

  if (Addr == 0) /*!< Address is QSPI_PAGESIZE aligned  */
  {
    if (NumOfPage == 0) /*!< NumByteToWrite < QSPI_PAGESIZE */
    {
      QSPI_DataNum = Size;
      W25Q128JV_Write(Address, buffer, QSPI_DataNum);
      W25Q128JV_AutoPollingMemReady();
    }
    else /*!< Size > QSPI_PAGESIZE */
    {
      while (NumOfPage--)
      {
        QSPI_DataNum = QSPI_PAGESIZE;
        W25Q128JV_Write(Address, buffer, QSPI_DataNum);
        W25Q128JV_AutoPollingMemReady();
        Address +=  QSPI_PAGESIZE;
        buffer += QSPI_PAGESIZE;
      }

      QSPI_DataNum = NumOfSingle;
      W25Q128JV_Write(Address, buffer, QSPI_DataNum);
      W25Q128JV_AutoPollingMemReady();
    }
  }
  else /*!< Address is not QSPI_PAGESIZE aligned  */
  {
    if (NumOfPage == 0) /*!< Size < QSPI_PAGESIZE */
    {
      if (NumOfSingle > count) /*!< (Size + Address) > QSPI_PAGESIZE */
      {
        temp = NumOfSingle - count;
        QSPI_DataNum = count;
        W25Q128JV_Write(Address, buffer, QSPI_DataNum);
        W25Q128JV_AutoPollingMemReady();
        Address +=  count;
        buffer += count;

        QSPI_DataNum = temp;
        W25Q128JV_Write(Address, buffer, QSPI_DataNum);
        W25Q128JV_AutoPollingMemReady();
      }
      else
      {
        QSPI_DataNum = Size;
        W25Q128JV_Write(Address, buffer, QSPI_DataNum);
        W25Q128JV_AutoPollingMemReady();
      }
    }
    else /*!< Size > QSPI_PAGESIZE */
    {
      Size -= count;
      NumOfPage =  Size / QSPI_PAGESIZE;
      NumOfSingle = Size % QSPI_PAGESIZE;

      QSPI_DataNum = count;

      W25Q128JV_Write(Address, buffer, QSPI_DataNum);
      W25Q128JV_AutoPollingMemReady();
      Address +=  count;
      buffer += count;

      while (NumOfPage--)
      {
        QSPI_DataNum = QSPI_PAGESIZE;

        W25Q128JV_Write(Address, buffer, QSPI_DataNum);
        W25Q128JV_AutoPollingMemReady();
        Address +=  QSPI_PAGESIZE;
        buffer += QSPI_PAGESIZE;
      }

      if (NumOfSingle != 0)
      {
        QSPI_DataNum = NumOfSingle;

        W25Q128JV_Write(Address, buffer, QSPI_DataNum);
        W25Q128JV_AutoPollingMemReady();
      }
    }
  }

	return 1;
}

/*******************************************************************************
 Description :
 Erase a full sector in the device
 Inputs :
 				SectrorAddress	: Start of sector
 outputs :
 				"1" : Operation succeeded
 				"0" : Operation failure
 Note : Not Mandatory for SRAM PSRAM and NOR_FLASH
********************************************************************************/
int SectorErase (uint32_t EraseStartAddress ,uint32_t EraseEndAddress)
{
	uint32_t BlockAddr;
	EraseStartAddress = EraseStartAddress -  EraseStartAddress % 0x10000;

	while (EraseEndAddress>=EraseStartAddress)
	{
		BlockAddr = EraseStartAddress & 0x0FFFFFFF;
		W25Q128JV_EraseBlock( BlockAddr);
        W25Q128JV_AutoPollingMemReady();
		EraseStartAddress += 0x10000;
	}
 	return 1;
}

/*******************************************************************************
 Description :
 Erase a full sector in the device
 Inputs :
 				SectrorAddress	: Start of sector
 outputs :
 				"1" : Operation succeeded
 				"0" : Operation failure
 Note : Not Mandatory for SRAM PSRAM and NOR_FLASH
********************************************************************************/
int MassErase (void)
{
	uint32_t BlockAddr = 0;

	while (BlockAddr < QSPI_FLASHSIZE)
	{
		W25Q128JV_EraseBlock( BlockAddr);
        W25Q128JV_AutoPollingMemReady();
        BlockAddr += QSPI_BLOCKSIZE;
	}
 	return 1;
}

/*******************************************************************************
 Description :
 Read data from the device
 Inputs :
 				Address 	: Write location
 				Size 		: Length in bytes
 				buffer 		: Address where to get the data to write
 outputs :
 				"1" 		: Operation succeeded
 				"0" 		: Operation failure
 Note : Not Mandatory
********************************************************************************/
int Read (uint32_t Address, uint32_t Size, uint8_t* Buffer)
{
	int i = 0;

	W25Q128JV_MemoryMapped();

	for (i=0; i < Size;i++)
	{
		*(uint8_t*)Buffer++ = *(uint8_t*)Address;
		Address ++;
	}

	return 1;
}

/*******************************************************************************
 Description :
 Verify the data
 Inputs :
 				MemoryAddr 	: Write location
 				RAMBufferAddr 	: RAM Address
 				Size 		: Length in bytes
 outputs :
 				"0" 		: Operation succeeded
 Note : Not Mandatory
********************************************************************************/
int Verify (uint32_t MemoryAddr, uint32_t RAMBufferAddr, uint32_t Size)
{
	uint32_t VerifiedData = 0;
	Size*=4;

	W25Q128JV_MemoryMapped();

  while (Size>VerifiedData)
  {
		if ( *(uint8_t*)MemoryAddr++ != *((uint8_t*)RAMBufferAddr + VerifiedData))
			return (MemoryAddr + VerifiedData);

		VerifiedData++;
  }

  return 0;
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
