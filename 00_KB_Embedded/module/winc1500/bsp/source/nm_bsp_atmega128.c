/**
 *
 * \file
 *
 * \brief This module contains SAMD21 BSP APIs implementation.
 *
 * Copyright (c) 2015 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */

#include "bsp/include/nm_bsp.h"
#include "common/include/nm_common.h"
#include "conf_winc.h"
#include "gpio.h"
#include "spi.h"
#include <avr/interrupt.h>
#include <util/delay.h>

static tpfNmBspIsr gpfIsr;

ISR (confWINC_INT_vect)
{
	#if defined(_ATMEGA128_)
	if (gpfIsr) {
		gpfIsr();
	}
	#elif defined(_ATMEGA328PB_)
	if (gpfIsr && (0 == gpioPinReadInput(confWINC_INT_PORT,confWINC_INT_PIN))) {
		gpfIsr();
	}
	#endif
}

/*
 *	@fn		init_chip_pins
 *	@brief	Initialize reset, chip enable and wake pin
 */
static void init_chip_pins(void)
{
	/* Configure control pins as output. */
	gpioPinSetMode(confWINC_RESET_PORT, confWINC_RESET_PIN, gpioOUTPUT);
	gpioPinSetMode(confWINC_WAKE_PORT, confWINC_WAKE_PIN, gpioOUTPUT);
	gpioPinSetMode(confWINC_CHIP_ENABLE_PORT, confWINC_CHIP_ENABLE_PIN, gpioOUTPUT);
}

/*
 *	@fn		nm_bsp_init
 *	@brief	Initialize BSP
 *	@return	0 in case of success and -1 in case of failure
 */
sint8 nm_bsp_init(void)
{
	gpfIsr = NULL;

	/* Initialize chip IOs. */
	init_chip_pins();

		/* TODO: Set timer? */
    /* Make sure a 1ms Systick is configured. */
    /*
    if (!(SysTick->CTRL & SysTick_CTRL_ENABLE_Msk && SysTick->CTRL & SysTick_CTRL_TICKINT_Msk)) {
	    delay_init();
    }
		*/

	/* Perform chip reset. */
	nm_bsp_reset();

	/* Enable glabal interrupt */
	sei();

	return M2M_SUCCESS;
}

/**
 *	@fn		nm_bsp_deinit
 *	@brief	De-iInitialize BSP
 *	@return	0 in case of success and -1 in case of failure
 */
sint8 nm_bsp_deinit(void)
{
	/* Configure control pins as input no pull up. */
	
	return M2M_SUCCESS;
}

/**
 *	@fn		nm_bsp_reset
 *	@brief	Reset NMC1500 SoC by setting CHIP_EN and RESET_N signals low,
 *           CHIP_EN high then RESET_N high
 */
void nm_bsp_reset(void)
{
	gpioPinSetOutput(confWINC_CHIP_ENABLE_PORT, confWINC_CHIP_ENABLE_PIN, gpioLOW);
	gpioPinSetOutput(confWINC_RESET_PORT, confWINC_RESET_PIN, gpioLOW);
	nm_bsp_sleep(100);
	gpioPinSetOutput(confWINC_CHIP_ENABLE_PORT, confWINC_CHIP_ENABLE_PIN, gpioHIGH);
	nm_bsp_sleep(10);
	gpioPinSetOutput(confWINC_RESET_PORT, confWINC_RESET_PIN, gpioHIGH);
	nm_bsp_sleep(100);
}

/*
 *	@fn		nm_bsp_sleep
 *	@brief	Sleep in units of mSec
 *	@param[IN]	u32TimeMsec
 *				Time in milliseconds
 */
void nm_bsp_sleep(uint32 u32TimeMsec)
{
	/* TODO: check this function */
	while (u32TimeMsec--) {
		_delay_ms(1);
	}
}

/*
 *	@fn		nm_bsp_register_isr
 *	@brief	Register interrupt service routine
 *	@param[IN]	pfIsr
 *				Pointer to ISR handler
 */
void nm_bsp_register_isr(tpfNmBspIsr pfIsr)
{
	/* TODO: What's this? */
	gpfIsr = pfIsr;

	/* Initialize interrupt GPIO */
	gpioPinSetMode(confWINC_INT_PORT, confWINC_INT_PIN, gpioINPUT_PULL_UP);
	
	/* Enable interrupt */
	gpioIntEnable();
}

/*
 *	@fn		nm_bsp_interrupt_ctrl
 *	@brief	Enable/Disable interrupts
 *	@param[IN]	u8Enable
 *				'0' disable interrupts. '1' enable interrupts
 */
void nm_bsp_interrupt_ctrl(uint8 u8Enable)
{
	if (u8Enable) {
		gpioIntEnable();
	} else {
		gpioIntDisable();
	}
}
