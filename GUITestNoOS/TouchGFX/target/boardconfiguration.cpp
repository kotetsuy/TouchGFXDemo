//{SPI2={}, USART3={}, RCC={}, CRC={}, NVIC={}, STMicroelectronics.X-CUBE-GFX1.0.0.1={}, TIM6={TIM6_DAC_LPTIM1_IRQn={interruptPremptionPriority=0, Subriority=0}}, SYS={}, GPIO={}}
//{socFtRPN=, Die=DIE460, socPtCPN=, socRPNSuperset=, socPackageType=, socDtRPN=, socName=STM32G081RBTx, socFtRPNSuperset=, socRPN=, Ram=36}
//[{isinused=false, mxcontextname=Cortex-M0+NS, mxipname=ADC1}, {isinused=false, mxcontextname=Cortex-M0+NS, mxipname=AES}, {isinused=false, mxcontextname=Cortex-M0+NS, mxipname=COMP1}, {isinused=false, mxcontextname=Cortex-M0+NS, mxipname=COMP2}, {isinused=true, mxcontextname=Cortex-M0+NS, mxipname=CRC}, {isinused=false, mxcontextname=Cortex-M0+NS, mxipname=DAC1}, {isinused=false, mxcontextname=Cortex-M0+NS, mxipname=FATFS}, {isinused=false, mxcontextname=Cortex-M0+NS, mxipname=FREERTOS}, {isinused=false, mxcontextname=Cortex-M0+NS, mxipname=GUI_INTERFACE}, {isinused=false, mxcontextname=Cortex-M0+NS, mxipname=HDMI_CEC}, {isinused=false, mxcontextname=Cortex-M0+NS, mxipname=I2C1}, {isinused=false, mxcontextname=Cortex-M0+NS, mxipname=I2C2}, {isinused=false, mxcontextname=Cortex-M0+NS, mxipname=I2S1}, {isinused=false, mxcontextname=Cortex-M0+NS, mxipname=IRTIM}, {isinused=false, mxcontextname=Cortex-M0+NS, mxipname=IWDG}, {isinused=false, mxcontextname=Cortex-M0+NS, mxipname=LPTIM1}, {isinused=false, mxcontextname=Cortex-M0+NS, mxipname=LPTIM2}, {isinused=false, mxcontextname=Cortex-M0+NS, mxipname=LPUART1}, {isinused=true, mxcontextname=Cortex-M0+NS, mxipname=RCC}, {isinused=false, mxcontextname=Cortex-M0+NS, mxipname=RNG}, {isinused=false, mxcontextname=Cortex-M0+NS, mxipname=RTC}, {isinused=false, mxcontextname=Cortex-M0+NS, mxipname=SPI1}, {isinused=true, mxcontextname=Cortex-M0+NS, mxipname=SPI2}, {isinused=true, mxcontextname=Cortex-M0+NS, mxipname=SYS}, {isinused=false, mxcontextname=Cortex-M0+NS, mxipname=TIM1}, {isinused=false, mxcontextname=Cortex-M0+NS, mxipname=TIM2}, {isinused=false, mxcontextname=Cortex-M0+NS, mxipname=TIM3}, {isinused=true, mxcontextname=Cortex-M0+NS, mxipname=TIM6}, {isinused=false, mxcontextname=Cortex-M0+NS, mxipname=TIM7}, {isinused=false, mxcontextname=Cortex-M0+NS, mxipname=TIM14}, {isinused=false, mxcontextname=Cortex-M0+NS, mxipname=TIM15}, {isinused=false, mxcontextname=Cortex-M0+NS, mxipname=TIM16}, {isinused=false, mxcontextname=Cortex-M0+NS, mxipname=TIM17}, {isinused=false, mxcontextname=Cortex-M0+NS, mxipname=TRACER_EMB}, {isinused=false, mxcontextname=Cortex-M0+NS, mxipname=UCPD1}, {isinused=false, mxcontextname=Cortex-M0+NS, mxipname=UCPD2}, {isinused=false, mxcontextname=Cortex-M0+NS, mxipname=USART1}, {isinused=false, mxcontextname=Cortex-M0+NS, mxipname=USART2}, {isinused=true, mxcontextname=Cortex-M0+NS, mxipname=USART3}, {isinused=false, mxcontextname=Cortex-M0+NS, mxipname=USART4}, {isinused=false, mxcontextname=Cortex-M0+NS, mxipname=USBPD}, {isinused=false, mxcontextname=Cortex-M0+NS, mxipname=WWDG}, {isinused=true, mxcontextname=Cortex-M0+NS, mxipname=GPIO}, {isinused=false, mxcontextname=Cortex-M0+NS, mxipname=DMA}, {isinused=true, mxcontextname=Cortex-M0+NS, mxipname=NVIC}, {isinused=true, mxcontextname=Cortex-M0+NS, mxipname=STMicroelectronics.X-CUBE-GFX1.0.0.1}]
//{Cortex-M0+NS={isSecure=false, coreName=ARM Cortex-M0+, longName=}}
//[CRC, SPI2, SYS, TIM6, USART3, NVIC, GPIO]

/**
 ******************************************************************************
  * File Name          : target/boardconfiguration.cpp
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
#include <touchgfx/hal/BoardConfiguration.hpp>
#include <texts/TypedTextDatabase.hpp>
#include <fonts/ApplicationFontProvider.hpp>
#include <gui/common/FrontendHeap.hpp>
#include <BitmapDatabase.hpp>
#include <platform/driver/lcd/LCD16bpp.hpp>
#include <platform/driver/touch/NoTouchController.hpp>
#include <touchgfx/hal/OSWrappers.hpp>
#include <touchgfx/hal/NoDMA.hpp>
#include <TouchGFXHAL.hpp>
#include <stm32f4xx_hal.h>
#include "ili9341.h"
extern "C" void touchgfx_init();
extern "C" void touchgfx_taskEntry();
extern "C" void hx8347d_displayOn(void);
extern uint32_t vsync_sem;
NoDMA dma;
NoTouchController tc;
LCD16bpp display;
static uint32_t animationstorage = 0;

static ApplicationFontProvider fontProvider;
static Texts texts;
static TouchGFXHAL hal(dma, display, tc, 320, 240);

ManyBlockAllocator<1024, 3, 2> frameBufferAllocator;

void touchgfx_init()
{
  hal.initialize();

  Bitmap::registerBitmapDatabase(BitmapDatabase::getInstance(),
                                 BitmapDatabase::getInstanceSize(),
                                 0, /* bitmapCache, */
                                 0, /* bitmapCacheSize, */
                                 0 /* numberOfDynamicBitmaps */);

  TypedText::registerTexts(&texts);
  Texts::setLanguage(0);

  FontManager::setFontProvider(&fontProvider);

  FrontendHeap& heap = FrontendHeap::getInstance();
  (void)heap; // we need to obtain the reference above to initialize the frontend heap.

  hal.registerEventListener(*(Application::getInstance()));
  hal.setFrameBufferAllocator(&frameBufferAllocator);
  hal.setFrameRefreshStrategy(HAL::REFRESH_STRATEGY_PARTIAL_FRAMEBUFFER);
  hal.setTouchSampleRate(1);
  hal.setFingerSize(1);

  // By default frame rate compensation is off.
  // Enable frame rate compensation to smooth out animations in case there is periodic slow frame rates.
  hal.setFrameRateCompensation(false);

  // This platform can handle simultaneous DMA and TFT accesses to SDRAM, so disable lock to increase performance.
  hal.lockDMAToFrontPorch(false);

}

void touchgfx_taskEntry()
{
  HAL::getInstance()->enableLCDControllerInterrupt();
  HAL::getInstance()->enableInterrupts();
  
  OSWrappers::waitForVSync();
  HAL::getInstance()->backPorchExited();

  while(1)
  {
      OSWrappers::waitForVSync();
      HAL::getInstance()->backPorchExited();
  }
}



//{tgfx_lock_dma_to_front_porch=false, tgfx_width=320, tgfx_block_size=1024, tgfx_height=240, tgfx_pixel_format=RGB565:16, tgfx_frame_rate_compensation=false, TouchGFXMonitor=null, tgfx_instrumentation=false, Start_Address=null, tgfx_mcu_family=m0+, EA_3_in_file1_param7=null, RefreshCount_SDRAM_Param=null, tgfx_oswrapper=NoOS, Use_SDRAM=null, tgfx_location=NA, tgfx_touch_sample_rate=1, tgfx_hardware_accelerator=dma_none, tgfx_buffering_strategy=Partial, tgfx_number_of_blocks=3, tgfx_finger_size=1}
//[]

