/*
 * kb_spi.h
 *
 *  Created on: Oct 25, 2016
 *      Author: Bumsik Kim
 */

#ifndef PERIPHERAL_KB_ADC_H_
#define PERIPHERAL_KB_ADC_H_

#include "kb_common_header.h"
#include "kb_gpio.h"

/*******************************************************************************
 * Forward declaration and matching manufacturer drivers.
 * API users can ignore this section
 ******************************************************************************/
#if defined(STM32)
    /* Match manufacturer library structures */
    typedef ADC_HandleTypeDef   kb_adc_internal_t;
#else
    #error "Please include kb_config.h in the source file or define device driver! (e.g. USE_HAL_DRIVER)."
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * Enumerations
 ******************************************************************************/
typedef enum _kb_adc_device_t {
    KB_ADC1 = 0, KB_ADC2, KB_ADC3
} kb_adc_device_t;

typedef enum _kb_adc_ch_t {
    KB_ADC_CH0 = 0, KB_ADC_CH1 , KB_ADC_CH2 , KB_ADC_CH3 , KB_ADC_CH4 , 
    KB_ADC_CH5    , KB_ADC_CH6 , KB_ADC_CH7 , KB_ADC_CH8 , KB_ADC_CH9 ,
    KB_ADC_CH10   , KB_ADC_CH11, KB_ADC_CH12, KB_ADC_CH13, KB_ADC_CH14,
    KB_ADC_CH15
} kb_adc_ch_t;

/*******************************************************************************
 * API object structures
 ******************************************************************************/
typedef struct _kb_adc_t {
    kb_adc_internal_t handler;
#ifdef KB_USE_PERIPHERAL_FREERTOS_LOCK
    SemaphoreHandle_t lock; // mutex lock
#endif
} kb_adc_t;

typedef struct _kb_adc_init_t {
    kb_adc_device_t device;
    kb_adc_ch_t channel;
} kb_adc_init_t;

/*******************************************************************************
 * API functions
 ******************************************************************************/
/* Initialization functions */
int kb_adc_init(kb_adc_t *obj, kb_adc_init_t *settings);
int kb_adc_pin(kb_gpio_port_t port, kb_gpio_pin_t pin);

/* Configuration functions */

/* Operation functions */
uint32_t kb_adc_measure(kb_adc_t *adc);

/* Lock operation */


#ifdef __cplusplus
}
#endif

#endif /* PERIPHERAL_KB_ADC_H_ */
