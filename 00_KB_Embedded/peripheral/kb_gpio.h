/*
 * kb_gpio.h
 *
 *  Created on: Oct 25, 2016
 *      Author: Bumsik Kim
 */

#ifndef PERIPHERAL_KB_GPIO_H_
#define PERIPHERAL_KB_GPIO_H_

#include "kb_common_source.h"

#if defined(STM32)
    // typedefs
    /* TODO: Think of a good design for GPIO */
    typedef void*   kb_gpio_port_t;
    typedef uint16_t    kb_gpio_pin_t;
    typedef GPIO_InitTypeDef 	kb_gpio_init_t;
    typedef GPIO_PinState 		kb_gpio_state_t;
    typedef	uint32_t			kb_gpio_pull_t;
    typedef enum {
        RISING_EDGE,
        FALLING_EDGE,
        BOTH_EDGE
    }kb_gpio_edge_t;
    // Pull state
    #define NOPULL		GPIO_NOPULL
    #define PULLUP		GPIO_PULLUP
    #define PULLDOWN	GPIO_PULLDOWN
    // Pin enums
    typedef enum {
        PA_0 = 0x00U, PA_1, PA_2, PA_3, PA_4, PA_5, PA_6, PA_7, PA_8, PA_9, PA_10, PA_11, PA_12, PA_13, PA_14, PA_15,
        PB_0, PB_1, PB_2, PB_3, PB_4, PB_5, PB_6, PB_7, PB_8, PB_9, PB_10, PB_11, PB_12, PB_13, PB_14, PB_15,
        PC_0, PC_1, PC_2, PC_3, PC_4, PC_5, PC_6, PC_7, PC_8, PC_9, PC_10, PC_11, PC_12, PC_13, PC_14, PC_15,
        PD_0, PD_1, PD_2, PD_3, PD_4, PD_5, PD_6, PD_7, PD_8, PD_9, PD_10, PD_11, PD_12, PD_13, PD_14, PD_15,
        PE_0, PE_1, PE_2, PE_3, PE_4, PE_5, PE_6, PE_7, PE_8, PE_9, PE_10, PE_11, PE_12, PE_13, PE_14, PE_15,
        PF_0, PF_1, PF_2, PF_3, PF_4, PF_5, PF_6, PF_7, PF_8, PF_9, PF_10, PF_11, PF_12, PF_13, PF_14, PF_15,
        PG_0, PG_1, PG_2, PG_3, PG_4, PG_5, PG_6, PG_7, PG_8, PG_9, PG_10, PG_11, PG_12, PG_13, PG_14, PG_15,
        PH_0, PH_1, PH_2, PH_3, PH_4, PH_5, PH_6, PH_7, PH_8, PH_9, PH_10, PH_11, PH_12, PH_13, PH_14, PH_15
    }kb_gpio_pin_t;
#else
    #error "Please define device driver (e.g. USE_HAL_DRIVER)\n"
#endif


#ifdef __cplusplus
extern "C"{
#endif

void kb_gpio_init(kb_gpio_port_t port, kb_gpio_pin_t pin, kb_gpio_init_t *gpio_init);
kb_gpio_state_t kb_gpio_read(kb_gpio_port_t port, kb_gpio_pin_t pin);
void kb_gpio_set(kb_gpio_port_t port, kb_gpio_pin_t pin, kb_gpio_state_t state);
void kb_gpio_toggle(kb_gpio_port_t port, kb_gpio_pin_t pin);

void kb_gpio_enable_clk(kb_gpio_port_t port);

int kb_gpio_isr_register(kb_gpio_port_t port, kb_gpio_pin_t pin, void (*callback)(void));
int kb_gpio_isr_deregister(kb_gpio_port_t port, kb_gpio_pin_t pin);
int kb_gpio_isr_enable(kb_gpio_port_t port, kb_gpio_pin_t pin, kb_gpio_init_t *gpio_init, kb_gpio_edge_t edge);
int kb_gpio_isr_disable(kb_gpio_port_t port, kb_gpio_pin_t pin);


#ifdef __cplusplus
}
#endif

#endif /* PERIPHERAL_KB_GPIO_H_ */
