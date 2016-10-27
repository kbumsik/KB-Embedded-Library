/*
 * kb_terminal.c
 *
 *  Created on: Oct 26, 2016
 *      Author: Bumsik Kim
 */

#include "kb_module_config.h"
#include "kb_terminal.h"
#include "kb_uart.h"
#include "stm32f4xx_hal_def.h"

int kb_terminal_init(void)
{
	kb_uart_tx_init(USART2, TERMINAL_TX_GPIO_Port, TERMINAL_TX_Pin);
	kb_uart_rx_init(USART2, TERMINAL_RX_GPIO_Port, TERMINAL_RX_Pin);
	return kb_uart_init(TERMINAL_UART, TERMINAL_BAUD_RATE);
}

int kb_terminal_puts(const char *str)
{
    return kb_uart_send_str(TERMINAL_UART, str, HAL_MAX_DELAY);
}

char *kb_terminal_gets(char *str)
{
	int result = kb_uart_receive(TERMINAL_UART, (uint8_t *)str, 80, HAL_MAX_DELAY);	// FIXME: more nice gets
	if (result != HAL_OK)
	{
		return NULL;
	}
	return str;
}

