/*
 * kb_spi.h
 *
 *  Created on: Oct 25, 2016
 *      Author: Bumsik Kim
 */

#ifndef PERIPHERAL_KB_SPI_H_
#define PERIPHERAL_KB_SPI_H_

#include "kb_gpio.h"
#include "stm32f4xx.h"

#if defined(USE_HAL_DRIVER)
	typedef SPI_TypeDef* kb_spi_t;
#else
	#error "Please define device driver! " __FILE__ "(e.g. USE_HAL_DRIVER)\n"
#endif

typedef enum{
	LEADING_RISING_EDGE = 0x01,
	LEADING_FALLING_EDGE = 0x02,
	TRAILING_RISING_EDGE = 0x03,
	TRAILING_FALLING_EDGE = 0x04,
}kb_spi_polarity_t;

#ifdef __cplusplus
extern "C"{
#endif

int kb_spi_init(kb_spi_t spi, kb_spi_polarity_t polarity);
int kb_spi_mosi_init(kb_spi_t spi, kb_gpio_port_t port, kb_gpio_pin_t pin);
int kb_spi_miso_init(kb_spi_t spi, kb_gpio_port_t port, kb_gpio_pin_t pin);
int kb_spi_sck_init(kb_spi_t spi, kb_gpio_port_t port, kb_gpio_pin_t pin);

int kb_spi_send(kb_spi_t spi, uint8_t *buf, uint16_t size, uint32_t timeout);

#ifdef __cplusplus
}
#endif

#endif /* PERIPHERAL_KB_SPI_H_ */
