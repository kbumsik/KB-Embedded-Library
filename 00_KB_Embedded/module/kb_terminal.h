/*
 * kb_terminal.h
 *
 *  Created on: Oct 26, 2016
 *      Author: Bumsik Kim
 */

#ifndef MODULE_KB_TERMINAL_H_
#define MODULE_KB_TERMINAL_H_

/*
 * uart.h
 *
 *  Created on: Dec 30, 2015
 *      Author: Bumsik Kim
 */

/* Includes */
#include "kb_module_config.h"
#include "stm32f4xx.h"

#ifndef TERMINAL_UART	// STM32 NUCLEO64 default
	#define TERMINAL_UART			USART2
	#define TERMINAL_BAUD_RATE		9600 // or 115200
	#define TERMINAL_TX_Pin 		GPIO_PIN_2
	#define TERMINAL_TX_GPIO_Port 	GPIOA
	#define TERMINAL_RX_Pin 		GPIO_PIN_3
	#define TERMINAL_RX_GPIO_Port 	GPIOA
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* global variables */
//extern UART_HandleTypeDef xUARTHandle;
//extern QueueHandle_t quUARTReceive;

int kb_terminal_init(void);
int kb_terminal_puts(const char *str);
char *kb_terminal_gets(char *str);

#ifdef __cplusplus
}
#endif

#endif /* MODULE_KB_TERMINAL_H_ */
