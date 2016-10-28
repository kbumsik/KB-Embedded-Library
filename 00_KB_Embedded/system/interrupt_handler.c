/*
 * exception_handler.c
 *
 *  Created on: Oct 20, 2016
 *      Author: Bumsik Kim
 */


#include "kb_tick.h"
#include "interrupt_handler.h"
#include "stm32f4xx_hal.h"
#include "faults.h"

#if defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7EM__)

void DebugMon_Handler (void)
{
#if defined(DEBUG)
  __DEBUG_BKPT();
#endif
  while (1)
    {
    }
}

#endif

void PendSV_Handler (void)
{
#if defined(DEBUG)
  __DEBUG_BKPT();
#endif
  while (1)
    {
    }
}

void SVC_Handler (void)
{
#if defined(DEBUG)
  __DEBUG_BKPT();
#endif
  while (1)
    {
    }
}

void SysTick_Handler (void)
{
	// DO NOT loop, just return.
	// Useful in case someone (like STM HAL) inadvertently enables SysTick.
	// TODO: put my timer
	kb_tick_inc_ms();
}
