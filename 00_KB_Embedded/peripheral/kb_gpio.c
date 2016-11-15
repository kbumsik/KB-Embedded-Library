/*
 * kb_gpio.c
 *
 *  Created on: Oct 26, 2016
 *      Author: Bumsik Kim
 */

#include "kb_common_source.h"
#include "kb_gpio.h"

// base name change. Used with kb_msg(). See @kb_base.h
#ifdef KB_MSG_BASE
    #undef KB_MSG_BASE
    #define KB_MSG_BASE "GPIO"
#endif


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

int kb_gpio_isr_enable(kb_gpio_port_t port, kb_gpio_pin_t pin,
        kb_gpio_edge_t edge, void (*callback)(void))
{
    
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
        KB_DEBUG_ERROR("Wrong port selected for clock!\r\n");
    }
    return;
}

/******************************************************************************
 * Interrupt Handlers
 ******************************************************************************/

void EXTI0_IRQHandler(void)
{

}
void EXTI1_IRQHandler(void)
{

}
void EXTI2_IRQHandler(void)
{

}
void EXTI3_IRQHandler(void)
{

}
void EXTI4_IRQHandler(void)
{

}

void EXTI9_5_IRQHandler(void)
{

}

void EXTI15_10_IRQHandler(void)
{

}