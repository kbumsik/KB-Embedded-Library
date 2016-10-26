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

/* TODO: Think of a good design for GPIO
typedef enum{
	INPUT,
	OUTPUT,
	OUTPUT_OPENDRAIN,
	ALT,
	ALT_OPENDRAIN
}kb_gpio_mode_t;

typedef enum{
	NOPULL,
	PULLUP,
	PULLDOWN
}kb_gpio_pull_t;

typedef enum{
	LOW,
	HIGH
}kb_gpio_state_t;
*/
#ifdef __cplusplus
extern "C"{
#endif

/*
int kb_gpio_mode(kb_gpio_port_t port, kb_gpio_pin_t pin, kb_gpio_mode_t mode);
int kb_gpio_pull(kb_gpio_port_t port, kb_gpio_pin_t pin, kb_gpio_pull_t pull);
int kb_gpio_alternate(kb_gpio_port_t port, kb_gpio_pin_t pin, uint32_t alternate); // TODO: More general solution

kb_gpio_state_t kb_gpio_read(kb_gpio_port_t port, kb_gpio_pin_t pin);
int kb_gpio_set(kb_gpio_port_t port, kb_gpio_pin_t pin, kb_gpio_state_t high_low);
int kb_gpio_toggle(kb_gpio_port_t port, kb_gpio_pin_t pin);
*/
#ifdef __cplusplus
}
#endif

#endif /* PERIPHERAL_KB_GPIO_H_ */
