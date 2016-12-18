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

#define _get_port_idx(pin)   (pin>>4)
#define _get_pin_idx(pin)    (pin%16)
void * _get_port(kb_gpio_pin_t pin);
uint16_t _get_pin(kb_gpio_pin_t pin);
IRQn_Type _get_irq_num(kb_gpio_pin_t pin);

static int _register_callback(kb_gpio_pin_t pin, void (*callback)(void));
static int _set_isr(kb_gpio_pin_t pin, uint8_t enable);
static void (* _callback_list[])(void);


/******************************************************************************
 * Function definitions
 ******************************************************************************/

void kb_gpio_init(kb_gpio_pin_t pin, kb_gpio_init_t *gpio_init)
{
    kb_gpio_enable_clk(pin);
    gpio_init->Pin = _get_pin(pin);
    HAL_GPIO_Init(_get_port(pin), gpio_init);
    return;
}


kb_gpio_state_t kb_gpio_read(kb_gpio_pin_t pin)
{
    return HAL_GPIO_ReadPin(_get_port(pin), _get_pin(pin));
}


void kb_gpio_set(kb_gpio_pin_t pin, kb_gpio_state_t state)
{
    HAL_GPIO_WritePin(_get_port(pin), _get_pin(pin), state);
    return;
}


void kb_gpio_toggle(kb_gpio_pin_t pin)
{
    HAL_GPIO_TogglePin(_get_port(pin), _get_pin(pin));
    return;
}


void kb_gpio_enable_clk(kb_gpio_pin_t pin)
{
    void *port = _get_port(pin);
    if(port == GPIOA) {
        __HAL_RCC_GPIOA_CLK_ENABLE();
    } else if(port == GPIOB) {
        __HAL_RCC_GPIOB_CLK_ENABLE();
    } else if(port == GPIOC) {
        __HAL_RCC_GPIOC_CLK_ENABLE();
    } else if(port == GPIOD) {
        __HAL_RCC_GPIOD_CLK_ENABLE();
    } else if(port == GPIOE) {
        __HAL_RCC_GPIOE_CLK_ENABLE();
    } else if(port == GPIOF) {
        __HAL_RCC_GPIOF_CLK_ENABLE();
    } else if(port == GPIOG) {
        __HAL_RCC_GPIOG_CLK_ENABLE();
    } else if(port == GPIOH) {
        __HAL_RCC_GPIOH_CLK_ENABLE();
    } else {
        KB_DEBUG_ERROR("Wrong port selected for clock!\r\n");
    }
    return;
}


int kb_gpio_isr_register(kb_gpio_pin_t pin, void (* callback)(void))
{
    return _register_callback(pin, callback);
}


int kb_gpio_isr_deregister(kb_gpio_pin_t pin)
{
    return _register_callback(pin, NULL);
}


int kb_gpio_isr_enable(kb_gpio_pin_t pin, kb_gpio_init_t *gpio_setting, kb_gpio_edge_t edge)
{
    // Set GPIO
    gpio_setting->Mode = ((edge == RISING_EDGE)?GPIO_MODE_IT_RISING:
            (edge == FALLING_EDGE)?GPIO_MODE_IT_FALLING:
            (edge == BOTH_EDGE)?GPIO_MODE_IT_RISING_FALLING:0);
    kb_gpio_init(pin, &gpio_setting);

    return _set_isr(pin, 1);
}


int kb_gpio_isr_disable(kb_gpio_pin_t pin)
{
    // Set GPIO
    kb_gpio_init_t gpio_setting = {
        .Pin = pin,
        .Mode = GPIO_MODE_INPUT,
        .Pull = GPIO_NOPULL,
        .Speed = GPIO_SPEED_LOW
    };
    kb_gpio_init(pin, &gpio_setting);

    return _set_isr(pin, 0);
}

/******************************************************************************
 * Privates
 ******************************************************************************/

void * _get_port(kb_gpio_pin_t pin)
{
    static const void * port_table[] = {
        GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH
    }
    return port_table[_get_port_idx(pin)];
}

uint16_t _get_pin(kb_gpio_pin_t pin)
{
    static const uint16_t pin_table[] = {
        GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3, GPIO_PIN_4, GPIO_PIN_5, 
        GPIO_PIN_6, GPIO_PIN_7, GPIO_PIN_8, GPIO_PIN_9, GPIO_PIN_10, GPIO_PIN_11, 
        GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14, GPIO_PIN_15
    }
    return pin_table[_get_pin_idx(pin)];
}

IRQn_Type _get_irq_num(kb_gpio_pin_t pin)
{
    static const IRQn_Type irq_num_table[] = {
        EXTI0_IRQn,     /* 0 */
        EXTI1_IRQn,     /* 1 */
        EXTI2_IRQn,     /* 2 */
        EXTI3_IRQn,     /* 3 */
        EXTI4_IRQn,     /* 4 */
        EXTI9_5_IRQn,   /* 5 */
        EXTI9_5_IRQn,   /* 6 */
        EXTI9_5_IRQn,   /* 7 */
        EXTI9_5_IRQn,   /* 8 */
        EXTI9_5_IRQn,   /* 9 */
        EXTI15_10_IRQn, /* 10 */
        EXTI15_10_IRQn, /* 11 */
        EXTI15_10_IRQn, /* 12 */
        EXTI15_10_IRQn, /* 13 */
        EXTI15_10_IRQn, /* 14 */
        EXTI15_10_IRQn  /* 15 */
    }
    return irq_num_table[_get_pin_idx(pin)];
}

static int _register_callback(kb_gpio_pin_t pin, void (*callback)(void))
{
    // get irq num and index
    IRQn_Type irq_num = _get_irq_num(pin);
    int idx = _get_pin_idx(pin);

    // check if a callback is already placed
    if(NULL != _callback_list[idx]) {
        KB_DEBUG_WARNING("Replacing an interrupt handler...\r\n");
    }

    // put the callback
    _callback_list[idx] = callback;
    return KB_OK;
}

static int _set_isr(kb_gpio_pin_t pin, uint8_t enable)
{
    // get irq num
    IRQn_Type irq_num = _get_irq_num(pin);
    
    HAL_NVIC_SetPriority(irq_num, 15, 0);  // TODO: Find a better group number

    // enable interrupt
    if (enable) {
        HAL_NVIC_EnableIRQ(irq_num);
    } else {
        HAL_NVIC_DisableIRQ(irq_num);
    }
    return KB_OK;
}

static void (*_callback_list[])(void) = {
    NULL,   // EXTI0_IRQn
    NULL,   // EXTI1_IRQn
    NULL,   // EXTI2_IRQn
    NULL,   // EXTI3_IRQn
    NULL,   // EXTI4_IRQn
    NULL,   // 5 // EXTI9_5_IRQn
    NULL,   // 6 // EXTI9_5_IRQn
    NULL,   // 7 // EXTI9_5_IRQn
    NULL,   // 8 // EXTI9_5_IRQn
    NULL,   // 9 // EXTI9_5_IRQn
    NULL,   // 10 // EXTI15_10_IRQn
    NULL,   // 11 // EXTI15_10_IRQn
    NULL,   // 12 // EXTI15_10_IRQn
    NULL,   // 13 // EXTI15_10_IRQn
    NULL,   // 14 // EXTI15_10_IRQn
    NULL   // 15 // EXTI15_10_IRQn
};

/******************************************************************************
 * Interrupt Handlers
 ******************************************************************************/

void EXTI0_IRQHandler(void)
{
    /* EXTI line interrupt detected */
    if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_0) != RESET) {
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_0);
        if(NULL != _callback_list[0]) {
            _callback_list[0]();
        }
    }
}
void EXTI1_IRQHandler(void)
{
    /* EXTI line interrupt detected */
    if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_1) != RESET) {
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_1);
        if(NULL != _callback_list[1]) {
            _callback_list[1]();
        }
    }
}
void EXTI2_IRQHandler(void)
{
    /* EXTI line interrupt detected */
    if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_2) != RESET) {
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_2);
        if(NULL != _callback_list[2]) {
            _callback_list[2]();
        }
    }
}
void EXTI3_IRQHandler(void)
{
    /* EXTI line interrupt detected */
    if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_3) != RESET) {
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_3);
        if(NULL != _callback_list[3]) {
            _callback_list[3]();
        }
    }
}
void EXTI4_IRQHandler(void)
{
    /* EXTI line interrupt detected */
    if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_4) != RESET) {
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_4);
        if(NULL != _callback_list[4]) {
            _callback_list[4]();
        }
    }
}
void EXTI9_5_IRQHandler(void)
{
    /* EXTI line interrupt detected */
    if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_5) != RESET) {
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_5);
        if(NULL != _callback_list[5]) {
            _callback_list[5]();
        }
    }
    if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_6) != RESET) {
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_6);
        if(NULL != _callback_list[6]) {
            _callback_list[6]();
        }
    }
    if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_7) != RESET) {
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_7);
        if(NULL != _callback_list[7]) {
            _callback_list[7]();
        }
    }
    if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_8) != RESET) {
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_8);
        if(NULL != _callback_list[8]) {
            _callback_list[8]();
        }
    }
    if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_9) != RESET) {
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_9);
        if(NULL != _callback_list[9]) {
            _callback_list[9]();
        }
    }
}
void EXTI15_10_IRQHandler(void)
{
    /* EXTI line interrupt detected */
    if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_10) != RESET) {
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_10);
        if(NULL != _callback_list[10]) {
            _callback_list[10]();
        }
    }
    if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_11) != RESET) {
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_11);
        if(NULL != _callback_list[11]) {
            _callback_list[11]();
        }
    }
    if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_12) != RESET) {
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_12);
        if(NULL != _callback_list[12]) {
            _callback_list[12]();
        }
    }
    if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_13) != RESET) {
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_13);
        if(NULL != _callback_list[13]) {
            _callback_list[13]();
        }
    }
    if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_14) != RESET) {
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_14);
        if(NULL != _callback_list[14]) {
            _callback_list[14]();
        }
    }
    if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_15) != RESET) {
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_15);
        if(NULL != _callback_list[15]) {
            _callback_list[15]();
        }
    }
}
