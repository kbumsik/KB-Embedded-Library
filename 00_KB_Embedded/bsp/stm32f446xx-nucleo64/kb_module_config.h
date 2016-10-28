/*
 * module_config.h
 *
 *  Created on: Oct 26, 2016
 *      Author: Bumsik Kim
 */

#ifndef BSP_STM32F446XX_NUCLEO64_KB_MODULE_CONFIG_H_
#define BSP_STM32F446XX_NUCLEO64_KB_MODULE_CONFIG_H_

// Terminal settings
#define TERMINAL_UART			USART2
#define TERMINAL_BAUD_RATE		9600 // or 115200
#define TERMINAL_TX_PORT 		GPIOA
#define TERMINAL_TX_PIN 		GPIO_PIN_2
#define TERMINAL_RX_PORT 		GPIOA
#define TERMINAL_RX_PIN 		GPIO_PIN_3

// HCMS_290X settings
#define HCMS_290X_SPI			SPI2
#define HCMS_290X_RS_PORT		GPIOC
#define HCMS_290X_RS_PIN		GPIO_PIN_4
#define HCMS_290X_RESET_PORT 	GPIOC
#define HCMS_290X_RESET_PIN		GPIO_PIN_5
#define HCMS_290X_CE_PORT		GPIOA
#define HCMS_290X_CE_PIN		GPIO_PIN_4
#define HCMS_290X_MOSI_PORT 	GPIOC
#define HCMS_290X_MOSI_PIN		GPIO_PIN_1
#define HCMS_290X_SCK_PORT		GPIOB
#define HCMS_290X_SCK_PIN		GPIO_PIN_10

#endif /* BSP_STM32F446XX_NUCLEO64_KB_MODULE_CONFIG_H_ */