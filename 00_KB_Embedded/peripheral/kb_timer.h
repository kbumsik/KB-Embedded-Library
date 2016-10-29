/*
 * kb_timer.h
 *
 *  Created on: Oct 27, 2016
 *      Author: Bumsik Kim
 */

#ifndef PERIPHERAL_KB_TIMER_H_
#define PERIPHERAL_KB_TIMER_H_

/* Includes */
#include "kb_base.h"
#include "kb_gpio.h"

#if defined(STM32)
	typedef TIM_TypeDef* kb_timer_t;
	#define TIMER1	TIM1
	#define TIMER2	TIM2
	#define TIMER3	TIM3
	#define TIMER4	TIM4
	#define TIMER5	TIM5
	#define TIMER6	TIM6
	#define TIMER7	TIM7
	#define TIMER8	TIM8
	#define TIMER9	TIM9
	#define TIMER10	TIM10
	#define TIMER11	TIM11
	#define TIMER12	TIM12
	#define TIMER13	TIM13
	#define TIMER14	TIM14
	typedef struct{
		uint32_t	clock_frequency;
		uint16_t	period;
	}kb_timer_init_t;
	typedef enum{
		CH_1 = TIM_CHANNEL_1,
		CH_2 = TIM_CHANNEL_2,
		CH_3 = TIM_CHANNEL_3,
		CH_4 = TIM_CHANNEL_4,
	}kb_timer_ch_t;
#else
	#error "Please define device driver! " __FILE__ "(e.g. USE_HAL_DRIVER)\n"
#endif

#ifdef __cplusplus
extern "C" {
#endif

int kb_timer_ch_pin(kb_timer_t timer, uint32_t baud_rate);

int kb_pwm_init(kb_timer_t timer, kb_timer_init_t *setting);

int kb_pwm_ch_set_percent(kb_timer_t timer, kb_timer_ch_t channel, uint8_t duty_cycle_percent);
// 1 permyriad = 0.01%. 10,000 permyriad = 1%. max 10,000 permyriad
int kb_pwm_ch_set_permyriad(kb_timer_t timer, kb_timer_ch_t channel, uint16_t duty_cycle_permyriad);
int kb_pwm_ch_start(kb_timer_t timer, kb_timer_ch_t channel);
int kb_pwm_ch_stop(kb_timer_t timer, kb_timer_ch_t channel);

#ifdef __cplusplus
}
#endif

#endif /* PERIPHERAL_KB_TIMER_H_ */
