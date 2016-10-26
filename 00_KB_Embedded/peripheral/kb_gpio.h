/*
 * kb_gpio.h
 *
 *  Created on: Oct 25, 2016
 *      Author: Bumsik Kim
 */

#ifndef PERIPHERAL_KB_GPIO_H_
#define PERIPHERAL_KB_GPIO_H_

#include "stm32f4xx.h"

#if defined(USE_HAL_DRIVER) // stm32 driver
	typedef GPIO_TypeDef* 	kb_gpio_port_t;
	typedef uint16_t 		kb_gpio_pin_t;
#else
	#error "Please define device driver (e.g. USE_HAL_DRIVER)\n"
#endif

/* TODO: Think of a good design for GPIO */
typedef GPIO_InitTypeDef kb_gpio_init_t;
typedef GPIO_PinState kb_gpio_state_t;

#ifdef __cplusplus
extern "C"{
#endif

void kb_gpio_init(kb_gpio_port_t port, kb_gpio_pin_t pin, kb_gpio_init_t *gpio_init);
kb_gpio_state_t kb_gpio_read(kb_gpio_port_t port, kb_gpio_pin_t pin);
void kb_gpio_set(kb_gpio_port_t port, kb_gpio_pin_t pin, kb_gpio_state_t state);
void kb_gpio_toggle(kb_gpio_port_t port, kb_gpio_pin_t pin);

void kb_gpio_enable_clk(kb_gpio_port_t port);

#ifdef __cplusplus
}
#endif

#endif /* PERIPHERAL_KB_GPIO_H_ */
