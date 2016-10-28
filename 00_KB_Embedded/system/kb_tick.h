/*
 * timer.h
 *
 *  Created on: Jan 7, 2016
 *      Author: Bumsik Kim
 */

#ifndef KB_TICK_H_
#define KB_TICK_H_

#include "kb_base.h"
#include "main.h"

#ifndef F_CPU_MHZ
	#define F_CPU_MHZ 180
	#warning "Define F_CPU_MHZ in main.h!\n"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef STM32
	void 		kb_tick_init(void);
	void 		kb_tick_inc_ms(void);
	uint32_t 	kb_tick_ms(void);
	void 		kb_delay_ms(volatile uint32_t delay_ms);
	uint32_t 	kb_tick_us(void);
	void 		kb_delay_us(volatile uint32_t delay_us);
#else
#include "stm32f4xx_hal.h"
	#define	 kb_tick_init()
	#define  kb_tick_inc_ms() 			HAL_IncTick()
	#define  kb_tick_ms() 			HAL_GetTick()
	#define  kb_delay_ms(delay_ms) HAL_Delay(delay_ms)
	uint32_t kb_tick_us(void);
	void     kb_delay_us(volatile uint32_t delay_us);
#endif



#ifdef __cplusplus
}
#endif

#endif /* KB_TIMER_H_ */
