/*
 * timer.h
 *
 *  Created on: Jan 7, 2016
 *      Author: Bumsik Kim
 */

#ifndef KB_TIMER_H_
#define KB_TIMER_H_

#include "main.h"
#include "stm32f4xx_hal.h"

#ifndef F_CPU_MHZ
	#define F_CPU_MHZ 180
	#warning "Define F_CPU_MHZ in main.h!\n"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef USE_HAL_DRIVER
	void 		kb_timer_init(void);
	void 		kb_timer_inc_ms(void);
	uint32_t 	kb_timer_get_ms(void);
	void 		kb_timer_delay_ms(volatile uint32_t delay_ms);
	uint32_t 	kb_timer_get_us(void);
	void 		kb_timer_delay_us(volatile uint32_t delay_us);
#else
#include "stm32f4xx_hal.h"
	#define	 kb_timer_init()
	#define  kb_timer_inc_ms() 			HAL_IncTick()
	#define  kb_timer_get_ms() 			HAL_GetTick()
	#define  kb_timer_delay_ms(delay_ms) HAL_Delay(delay_ms)
	uint32_t kb_timer_get_us(void);
	void     kb_timer_delay_us(volatile uint32_t delay_us);


#endif



#ifdef __cplusplus
}
#endif

#endif /* KB_TIMER_H_ */
