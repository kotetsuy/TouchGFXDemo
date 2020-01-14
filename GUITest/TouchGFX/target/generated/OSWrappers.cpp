/**
  ******************************************************************************
  * File Name          : OSWrappers.cpp
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
#include <touchgfx/hal/OSWrappers.hpp>
#include <stm32f4xx_hal.h>
#include <touchgfx/hal/GPIO.hpp>
#include <touchgfx/hal/HAL.hpp>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

static xSemaphoreHandle frame_buffer_sem;
static xQueueHandle vsync_q = 0;

using namespace touchgfx;

// Just a dummy value to insert in the VSYNC queue.
static uint8_t dummy = 0x5a;

/*
 * Initialize frame buffer semaphore and queue/mutex for VSYNC signal.
 */
void OSWrappers::initialize()
{
    vSemaphoreCreateBinary(frame_buffer_sem);
    // Create a queue of length 1
    vsync_q = xQueueGenericCreate(1, 1, 0);
}

/*
 * Take the frame buffer semaphore. Blocks until semaphore is available.
 */
void OSWrappers::takeFrameBufferSemaphore()
{
    xSemaphoreTake(frame_buffer_sem, portMAX_DELAY);
}

/*
 * Release the frame buffer semaphore.
 */
void OSWrappers::giveFrameBufferSemaphore()
{
    xSemaphoreGive(frame_buffer_sem);
}

/*
 * Attempt to obtain the frame buffer semaphore. If semaphore is not available, do
 * nothing.
 *
 * Note must return immediately! This function does not care who has the taken the semaphore,
 * it only serves to make sure that the semaphore is taken by someone.
 */
void OSWrappers::tryTakeFrameBufferSemaphore()
{
    xSemaphoreTake(frame_buffer_sem, 0);
}

/*
 * Release the frame buffer semaphore in a way that is safe in interrupt context. Called
 * from ISR.
 *
 * Release the frame buffer semaphore in a way that is safe in interrupt context.
 * Called from ISR.
 */
void OSWrappers::giveFrameBufferSemaphoreFromISR()
{
    // Since this is called from an interrupt, FreeRTOS requires special handling to trigger a
    // re-scheduling. May be applicable for other OSes as well.
    portBASE_TYPE px = pdFALSE;
    xSemaphoreGiveFromISR(frame_buffer_sem, &px);
    portEND_SWITCHING_ISR(px);
}

/*
 * Signal that a VSYNC has occurred. Should make the vsync queue/mutex available.
 *
 * Note This function is called from an ISR, and should (depending on OS) trigger a
 * scheduling.
 */
void OSWrappers::signalVSync()
{
    if (vsync_q)
    {
        // Since this is called from an interrupt, FreeRTOS requires special handling to trigger a
        // re-scheduling. May be applicable for other OSes as well.
        portBASE_TYPE px = pdFALSE;
        xQueueSendFromISR(vsync_q, &dummy, &px);
        portEND_SWITCHING_ISR(px);
    }
}

/*
 * This function blocks until a VSYNC occurs.
 *
 * Note This function must first clear the mutex/queue and then wait for the next one to
 * occur.
 */
void OSWrappers::waitForVSync()
{
    // First make sure the queue is empty, by trying to remove an element with 0 timeout.
    xQueueReceive(vsync_q, &dummy, 0);

    // Then, wait for next VSYNC to occur.
    xQueueReceive(vsync_q, &dummy, portMAX_DELAY);
}

/*
 * A function that causes executing task to sleep for a number of milliseconds.
 *
 * A function that causes executing task to sleep for a number of milliseconds.
 * This function is OPTIONAL. It is only used by the TouchGFX in the case of
 * a specific frame refresh strategy (REFRESH_STRATEGY_OPTIM_SINGLE_BUFFER_TFT_CTRL).
 * Due to backwards compatibility, in order for this function to be useable by the HAL
 * the function must be explicitly registered:
 * hal.registerTaskDelayFunction(&OSWrappers::taskDelay)
 *
 * see HAL::setFrameRefreshStrategy(FrameRefreshStrategy s)
 * see HAL::registerTaskDelayFunction(void (*delayF)(uint16_t))
 */
void OSWrappers::taskDelay(uint16_t ms)
{
    vTaskDelay(ms);
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
