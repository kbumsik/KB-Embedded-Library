/*
 * kb_gpio.c
 *
 *  Created on: Oct 26, 2016
 *      Author: Bumsik Kim
 */

#include "kb_gpio.h"

void kb_gpio_init(kb_gpio_port_t port, kb_gpio_pin_t pin, kb_gpio_init_t *gpio_init)
{
	kb_gpio_enable_clk(port);
	gpio_init->Pin = pin;
	HAL_GPIO_Init(port, gpio_init);
	return;
}

kb_gpio_state_t kb_gpio_read(kb_gpio_port_t port, kb_gpio_pin_t pin)
{
	return HAL_GPIO_ReadPin(port, pin);
}

void kb_gpio_set(kb_gpio_port_t port, kb_gpio_pin_t pin, kb_gpio_state_t state)
{
	HAL_GPIO_WritePin(port, pin, state);
	return;
}


void kb_gpio_toggle(kb_gpio_port_t port, kb_gpio_pin_t pin)
{
	HAL_GPIO_TogglePin(port, pin);
	return;
}

void kb_gpio_enable_clk(kb_gpio_port_t port)
{
	if(port == GPIOA)
	{
		__GPIOA_CLK_ENABLE();
	}
	else if(port == GPIOB)
	{
		__GPIOB_CLK_ENABLE();
	}
	else if(port == GPIOC)
	{
		__GPIOC_CLK_ENABLE();
	}
	else if(port == GPIOD)
	{
		__GPIOD_CLK_ENABLE();
	}
	else if(port == GPIOE)
	{
		__GPIOE_CLK_ENABLE();
	}
	else if(port == GPIOF)
	{
		__GPIOF_CLK_ENABLE();
	}
	else if(port == GPIOG)
	{
		__GPIOG_CLK_ENABLE();
	}
	else if(port == GPIOH)
	{
		__GPIOH_CLK_ENABLE();
	}
	else
	{
		// TODO: Error management here.
	}
	return;
}
