/*
 * kb_timer.c
 *
 *  Created on: Oct 27, 2016
 *      Author: Bumsik Kim
 */

#include "kb_common_source.h"
#include "kb_timer.h"
#include "kb_alternate_pins.h"

// base name change. Used with kb_msg(). See @kb_base.h
#ifdef KB_MSG_BASE
    #undef KB_MSG_BASE
    #define KB_MSG_BASE "TIMER"
#endif

static uint32_t get_bus_freq_(kb_timer_t timer);
static TIM_HandleTypeDef *get_handler (kb_timer_t timer);
static void enable_timer_clk_ (kb_timer_t timer);

#if defined(STM32F446xx)
    static TIM_HandleTypeDef timer_1_h_ = {.Instance = TIM1};
    static TIM_HandleTypeDef timer_2_h_ = {.Instance = TIM2};
    static TIM_HandleTypeDef timer_3_h_ = {.Instance = TIM3};
    static TIM_HandleTypeDef timer_4_h_ = {.Instance = TIM4};
    static TIM_HandleTypeDef timer_5_h_ = {.Instance = TIM5};
    static TIM_HandleTypeDef timer_6_h_ = {.Instance = TIM6};
    static TIM_HandleTypeDef timer_7_h_ = {.Instance = TIM7};
    static TIM_HandleTypeDef timer_8_h_ = {.Instance = TIM8};
    static TIM_HandleTypeDef timer_9_h_ = {.Instance = TIM9};
    static TIM_HandleTypeDef timer_10_h_ = {.Instance = TIM10};
    static TIM_HandleTypeDef timer_11_h_ = {.Instance = TIM11};
    static TIM_HandleTypeDef timer_12_h_ = {.Instance = TIM12};
    static TIM_HandleTypeDef timer_13_h_ = {.Instance = TIM13};
    static TIM_HandleTypeDef timer_14_h_ = {.Instance = TIM14};
#else
    #error "Please define device!"
#endif


int kb_timer_ch_pin(kb_timer_t timer, kb_timer_ch_t channel, kb_gpio_port_t port, kb_gpio_pin_t pin, kb_gpio_pull_t pull)
{
    TIM_HandleTypeDef* handler = get_handler(timer);
    if (NULL == handler)
    {
        return KB_ERROR;
    }
    uint32_t alternate;
    switch (channel)
    {
    case CH_1:
        alternate = GPIO_TIM_CH1_AF_(handler->Instance, port, pin);
        break;
    case CH_2:
        alternate = GPIO_TIM_CH2_AF_(handler->Instance, port, pin);
        break;
    case CH_3:
        alternate = GPIO_TIM_CH3_AF_(handler->Instance, port, pin);
        break;
    case CH_4:
        alternate = GPIO_TIM_CH4_AF_(handler->Instance, port, pin);
        break;
    default:
        KB_DEBUG_ERROR("Choose correct channel!\r\n");
        return KB_ERROR;
    }
    if (alternate == KB_WRONG_PIN)
    {
        KB_DEBUG_ERROR("Wrong MOSI pin! Find a correct one.\r\n");
        return KB_ERROR;
    }
    kb_gpio_enable_clk(port);
    // Init GPIOs
    kb_gpio_init_t gpio_setting = {
        .Mode = GPIO_MODE_AF_PP,
        .Pull = pull,
        .Alternate = alternate,
        .Speed = GPIO_SPEED_FREQ_VERY_HIGH // 50MHz
    };
    kb_gpio_init(port, pin, &gpio_setting);
    return KB_OK;
}


int kb_pwm_init(kb_timer_t timer, kb_pwm_init_t *settings)
{
    // get handler and enable timer
    TIM_HandleTypeDef* handler = get_handler(timer);
    if (NULL == handler)
    {
        return KB_ERROR;
    }
    enable_timer_clk_(timer);

    // Timer init
    handler->Init.CounterMode = TIM_COUNTERMODE_UP;
    handler->Init.Period = settings->period;
    handler->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    handler->State = HAL_TIM_STATE_RESET;

    //
    /*	f_tim = f_clk/(psc + 1).  (from datasheet)
     * 	psc = f_clk/f_tim - 1
     */
    uint32_t freq;
    handler->Init.Prescaler = get_bus_freq_(timer)/settings->clock_frequency - 1;
    freq = get_bus_freq_(timer)/(handler->Init.Prescaler + 1);	// TODO: manage it more nicely.
    if (handler->Init.Prescaler > UINT16_MAX)
    {
        handler->Init.ClockDivision = TIM_CLOCKDIVISION_DIV2;
        handler->Init.Prescaler >>= 1;
        freq = (get_bus_freq_(timer)>>1)/(handler->Init.Prescaler + 1);
        if (handler->Init.Prescaler > UINT16_MAX)
        {
            handler->Init.ClockDivision = TIM_CLOCKDIVISION_DIV4;
            handler->Init.Prescaler >>= 1;
            freq = (get_bus_freq_(timer)>>1)/(handler->Init.Prescaler + 1);
        }
    }
    KB_DEBUG_MSG("Requested clock freq: %lu\r\n", settings->clock_frequency);
    KB_DEBUG_MSG("Requested pluse freq: %lu\r\n", settings->clock_frequency/settings->period);
    KB_DEBUG_MSG("Selected clock freq: %lu\r\n", freq);
    KB_DEBUG_MSG("Selected pulse freq: %lu\r\n", freq/handler->Init.Period);
    // good to go

    int8_t status = HAL_TIM_PWM_Init(handler);
    KB_CONVERT_STATUS(status);
    if(KB_OK != status)
    {
        KB_DEBUG_WARNING("Error init timer device!\r\n");
    }
    return  (kb_status_t)status;
}


int kb_pwm_percent(kb_timer_t timer, kb_timer_ch_t channel, uint8_t	duty_cycle_percent)
{
    return kb_pwm_permyriad(timer, channel, duty_cycle_percent * 100);
}


int kb_pwm_permyriad(kb_timer_t timer, kb_timer_ch_t channel, uint16_t duty_cycle_permyriad) // 1 permyriad = 0.01%. 100 permyriad = 1%. max 10000 permyriad
{
    // select handler
    TIM_HandleTypeDef* handler = get_handler(timer);
    if (NULL == handler)
    {
        return KB_ERROR;
    }

    // make configuration
    TIM_OC_InitTypeDef config;
    config.OCMode = TIM_OCMODE_PWM1;
    config.OCPolarity = TIM_OCPOLARITY_HIGH;
    config.OCFastMode = TIM_OCFAST_DISABLE;
    config.OCIdleState = TIM_OCIDLESTATE_RESET;
    config.OCNIdleState = TIM_OCNIDLESTATE_RESET;

    // setting duty cycle
    if(duty_cycle_permyriad > 10000)
    {
        KB_DEBUG_WARNING("Duty cycle is > 10,000 permyriad.\r\n");
        duty_cycle_permyriad = 10000;
    }
    uint16_t period = handler->Init.Period;
    uint16_t pulse_width = ((uint32_t)period * duty_cycle_permyriad)/10000;
    config.Pulse = pulse_width;

    int8_t status = HAL_TIM_PWM_ConfigChannel(handler, &config, channel);
    KB_CONVERT_STATUS(status);
    if(KB_OK != status)
    {
        KB_DEBUG_WARNING("Error setting PWM ch!\r\n");
    }
    return  (kb_status_t)status;
}


int kb_pwm_start(kb_timer_t timer, kb_timer_ch_t channel)
{
    // get handler and enable timer
    TIM_HandleTypeDef* handler = get_handler(timer);
    if (NULL == handler)
    {
        return KB_ERROR;
    }

    int8_t status;
    switch (channel)
    {
    case CH_1:
        status = HAL_TIM_PWM_Start(handler, TIM_CHANNEL_1);
        break;
    case CH_2:
        status = HAL_TIM_PWM_Start(handler, TIM_CHANNEL_2);
        break;
    case CH_3:
        status = HAL_TIM_PWM_Start(handler, TIM_CHANNEL_3);
        break;
    case CH_4:
        status = HAL_TIM_PWM_Start(handler, TIM_CHANNEL_4);
        break;
    default:
        KB_DEBUG_ERROR("Choose correct channel!\r\n");
        return KB_ERROR;
    }

    KB_CONVERT_STATUS(status);
    if(KB_OK != status)
    {
        KB_DEBUG_WARNING("Error starting PWM ch!\r\n");
    }
    return status;
}


int kb_pwm_stop(kb_timer_t timer, kb_timer_ch_t channel)
{
    // get handler and enable timer
    TIM_HandleTypeDef* handler = get_handler(timer);
    if (NULL == handler)
    {
        return KB_ERROR;
    }

    int8_t status;
    switch (channel)
    {
    case CH_1:
        status = HAL_TIM_PWM_Stop(handler, TIM_CHANNEL_1);
        break;
    case CH_2:
        status = HAL_TIM_PWM_Stop(handler, TIM_CHANNEL_2);
        break;
    case CH_3:
        status = HAL_TIM_PWM_Stop(handler, TIM_CHANNEL_3);
        break;
    case CH_4:
        status = HAL_TIM_PWM_Stop(handler, TIM_CHANNEL_4);
        break;
    default:
        KB_DEBUG_ERROR("Choose correct channel!\r\n");
        return KB_ERROR;
    }
    KB_CONVERT_STATUS(status);
    if(KB_OK != status)
    {
        KB_DEBUG_WARNING("Error stopping PWM ch!\r\n");
    }
    return status;
}


int kb_encoder_init(kb_timer_t timer, kb_encoder_init_t *setting)
{
    // get handler and enable timer
    TIM_HandleTypeDef* handler = get_handler(timer);
    if (NULL == handler)
    {
        return KB_ERROR;
    }
    enable_timer_clk_(timer);

    handler->Init.Period = 0xffffffff; //0xFFFF
    handler->Init.Prescaler = setting->prescaler;
    handler->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    handler->Init.RepetitionCounter = 0;

    TIM_Encoder_InitTypeDef encoder_config;
    encoder_config.EncoderMode = TIM_ENCODERMODE_TI12;

    switch(setting->direction)
    {
    case CW:
        handler->Init.CounterMode = TIM_COUNTERMODE_UP;

        encoder_config.IC1Polarity = TIM_ICPOLARITY_RISING; //TIM_ICPOLARITY_RISING;
        encoder_config.IC1Selection = TIM_ICSELECTION_DIRECTTI;
        encoder_config.IC1Prescaler = TIM_ICPSC_DIV1;
        encoder_config.IC1Filter = 0xf;
    
        encoder_config.IC2Polarity = TIM_ICPOLARITY_FALLING; //TIM_ICPOLARITY_RISING;
        encoder_config.IC2Selection = TIM_ICSELECTION_DIRECTTI;
        encoder_config.IC2Prescaler = TIM_ICPSC_DIV1;
        encoder_config.IC2Filter = 0xf;
        break;
    case CCW:
        handler->Init.CounterMode = TIM_COUNTERMODE_DOWN;

        encoder_config.IC1Polarity = TIM_ICPOLARITY_RISING; //TIM_ICPOLARITY_RISING;
        encoder_config.IC1Selection = TIM_ICSELECTION_DIRECTTI;
        encoder_config.IC1Prescaler = TIM_ICPSC_DIV1;
        encoder_config.IC1Filter = 0xf;
    
        encoder_config.IC2Polarity = TIM_ICPOLARITY_RISING; //TIM_ICPOLARITY_RISING;
        encoder_config.IC2Selection = TIM_ICSELECTION_DIRECTTI;
        encoder_config.IC2Prescaler = TIM_ICPSC_DIV1;
        encoder_config.IC2Filter = 0xf;
        break;
    default:
        KB_DEBUG_ERROR("Incorrect encoder direction");
    }

    int8_t status = HAL_TIM_Encoder_Init(handler, &encoder_config);
    KB_CONVERT_STATUS(status);
    if(KB_OK != status)
    {
        KB_DEBUG_WARNING("Error init encoder!\r\n");
    }
    return status;
}


int kb_encoder_start(kb_timer_t timer)
{
    // get handler and enable timer
    TIM_HandleTypeDef* handler = get_handler(timer);
    if (NULL == handler)
    {
        return KB_ERROR;
    }

    int8_t status = HAL_TIM_Encoder_Start(handler, TIM_CHANNEL_ALL);
    KB_CONVERT_STATUS(status);
    if(KB_OK != status)
    {
        KB_DEBUG_WARNING("Error starting Encoder!\r\n");
    }
    return status;
}


int kb_encoder_stop(kb_timer_t timer)
{
    // get handler and enable timer
    TIM_HandleTypeDef* handler = get_handler(timer);
    if (NULL == handler)
    {
        return KB_ERROR;
    }

    int8_t status = HAL_TIM_Encoder_Stop(handler, TIM_CHANNEL_ALL);
    KB_CONVERT_STATUS(status);
    if(KB_OK != status)
    {
        KB_DEBUG_WARNING("Error stopping Encoder!\r\n");
    }
    return status;
}


int32_t kb_encoder_set(kb_timer_t timer, int32_t input)
{
    // get handler and enable timer
    TIM_HandleTypeDef* handler = get_handler(timer);
    if (NULL == handler)
    {
        return 0;
    }
    handler->Instance->CNT = input;
    return handler->Instance->CNT;
}


int32_t kb_encoder_count(kb_timer_t timer)
{
    // get handler and enable timer
    TIM_HandleTypeDef* handler = get_handler(timer);
    if (NULL == handler)
    {
        return 0;
    }
    return handler->Instance->CNT;
}


static uint32_t get_bus_freq_(kb_timer_t timer)
{
    RCC_ClkInitTypeDef rcc_config;
    uint32_t flash_latency;
    uint8_t timer_multiplier = 1;
    HAL_RCC_GetClockConfig(&rcc_config, &flash_latency);
    if ((timer == TIMER2) || (timer == TIMER3) || (timer == TIMER4) || (timer == TIMER5) || (timer == TIMER6)
            || (timer == TIMER7) || (timer == TIMER12) || (timer == TIMER13) || (timer == TIMER14))
    {	// APB1
        if(rcc_config.APB1CLKDivider != RCC_HCLK_DIV1)
        {	// See RCC datasheet
            timer_multiplier = 2;
        }
        return HAL_RCC_GetPCLK1Freq() * timer_multiplier;
    }
    else if ((timer == TIMER1) || (timer == TIMER8) || (timer == TIMER9) || (timer == TIMER10) || (timer == TIMER11))
    {	// APB2
        if(rcc_config.APB2CLKDivider != RCC_HCLK_DIV1)
        {	// See RCC datasheet
            timer_multiplier = 2;
        }
        return HAL_RCC_GetPCLK2Freq() * timer_multiplier;
    }
    KB_DEBUG_ERROR("Wrong TIM device! Find a correct one.\r\n");
    return 0;
}


static TIM_HandleTypeDef *get_handler (kb_timer_t timer)
{
    if (timer == TIMER1)
    {
        return &timer_1_h_;
    }
    else if (timer == TIMER2)
    {
        return &timer_2_h_;
    }
    else if (timer == TIMER3)
    {
        return &timer_3_h_;
    }
    else if (timer == TIMER4)
    {
        return &timer_4_h_;
    }
    else if (timer == TIMER5)
    {
        return &timer_5_h_;
    }
    else if (timer == TIMER6)
    {
        return &timer_6_h_;
    }
    else if (timer == TIMER7)
    {
        return &timer_7_h_;
    }
    else if (timer == TIMER8)
    {
        return &timer_8_h_;
    }
    else if (timer == TIMER9)
    {
        return &timer_9_h_;
    }
    else if (timer == TIMER10)
    {
        return &timer_10_h_;
    }
    else if (timer == TIMER11)
    {
        return &timer_11_h_;
    }
    else if (timer == TIMER12)
    {
        return &timer_12_h_;
    }
    else if (timer == TIMER13)
    {
        return &timer_13_h_;
    }
    else if (timer == TIMER14)
    {
        return &timer_14_h_;
    }
    else
    {
        KB_DEBUG_ERROR("Wrong Timer device selected!\r\n");
        return NULL;
    }
}


static void enable_timer_clk_ (kb_timer_t timer)
{
    if (timer == TIMER1)
    {
        __TIM1_CLK_ENABLE();
    }
    else if (timer == TIMER2)
    {
        __TIM2_CLK_ENABLE();
    }
    else if (timer == TIMER3)
    {
        __TIM3_CLK_ENABLE();
    }
    else if (timer == TIMER4)
    {
        __TIM4_CLK_ENABLE();
    }
    else if (timer == TIMER5)
    {
        __TIM5_CLK_ENABLE();
    }
    else if (timer == TIMER6)
    {
        __TIM6_CLK_ENABLE();
    }
    else if (timer == TIMER7)
    {
        __TIM7_CLK_ENABLE();
    }
    else if (timer == TIMER8)
    {
        __TIM8_CLK_ENABLE();
    }
    else if (timer == TIMER9)
    {
        __TIM9_CLK_ENABLE();
    }
    else if (timer == TIMER10)
    {
        __TIM10_CLK_ENABLE();
    }
    else if (timer == TIMER11)
    {
        __TIM11_CLK_ENABLE();
    }
    else if (timer == TIMER12)
    {
        __TIM12_CLK_ENABLE();
    }
    else if (timer == TIMER13)
    {
        __TIM13_CLK_ENABLE();
    }
    else if (timer == TIMER14)
    {
        __TIM14_CLK_ENABLE();
    }
    else
    {
        KB_DEBUG_ERROR("Wrong Timer device!\r\n");
    }
    return;
}
