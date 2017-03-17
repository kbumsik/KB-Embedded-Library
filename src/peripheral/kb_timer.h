/*
 * kb_timer.h
 *
 *  Created on: Oct 27, 2016
 *      Author: Bumsik Kim
 */

#ifndef PERIPHERAL_KB_TIMER_H_
#define PERIPHERAL_KB_TIMER_H_

/* Includes */
#include "kb_common_header.h"
#include "kb_gpio.h"

#if defined(STM32)
    typedef enum{
        TIMER1,
        TIMER2,
        TIMER3,
        TIMER4,
        TIMER5,
        TIMER6,
        TIMER7,
        TIMER8,
        TIMER9,
        TIMER10,
        TIMER11,
        TIMER12,
        TIMER13,
        TIMER14
    }kb_timer_t;
    typedef enum{
        CH_1 = TIM_CHANNEL_1, // 0x01U,
        CH_2 = TIM_CHANNEL_2, // 0x02U,
        CH_3 = TIM_CHANNEL_3, // 0x03U,
        CH_4 = TIM_CHANNEL_4  //0x04U,
    }kb_timer_ch_t;
    typedef enum{
        CW,
        CCW
    }kb_encoder_dir_t;
    typedef struct{
        uint32_t	clock_frequency;
        uint16_t	period;
    }kb_pwm_init_t;
    typedef struct{
        kb_encoder_dir_t direction;
        uint16_t	prescaler;
    }kb_encoder_init_t;
#else
    #error "Please define device driver! " __FILE__ "(e.g. USE_HAL_DRIVER)\n"
#endif


#ifdef __cplusplus
extern "C" {
#endif

// TODO: generic timer function
int kb_timer_ch_pin(kb_timer_t timer, kb_timer_ch_t channel, kb_gpio_port_t port, kb_gpio_pin_t pin, kb_gpio_pull_t pull);

// PWM functions
int kb_pwm_init(kb_timer_t timer, kb_pwm_init_t *setting);
int kb_pwm_percent(kb_timer_t timer, kb_timer_ch_t channel, uint8_t duty_cycle_percent);
// 1 permyriad = 0.01%. 10,000 permyriad = 1%. max 10,000 permyriad
int kb_pwm_permyriad(kb_timer_t timer, kb_timer_ch_t channel, uint16_t duty_cycle_permyriad);
int kb_pwm_start(kb_timer_t timer, kb_timer_ch_t channel);
int kb_pwm_stop(kb_timer_t timer, kb_timer_ch_t channel);

// quadrature encoder
int 	kb_encoder_init(kb_timer_t timer, kb_encoder_init_t *setting);
int 	kb_encoder_start(kb_timer_t timer);
int 	kb_encoder_stop(kb_timer_t timer);
int32_t kb_encoder_set(kb_timer_t timer, int32_t input);
int32_t kb_encoder_count(kb_timer_t timer);

#ifdef __cplusplus
}
#endif

#endif /* PERIPHERAL_KB_TIMER_H_ */
