/*
 * kb_spi.c
 *
 *  Created on: Oct 25, 2016
 *      Author: Bumsik Kim
 */

#include "kb_spi.h"
#include "kb_alternate_pins.h"
#include "stm32f4xx.h"

#if defined(STM32F446xx)
	static SPI_HandleTypeDef spi_1_h_;
	static SPI_HandleTypeDef spi_2_h_;
	static SPI_HandleTypeDef spi_3_h_;
	static SPI_HandleTypeDef spi_4_h_;
#else
	#error "Please define device! " __FILE__ "\n"
#endif

int kb_spi_init(kb_spi_t spi_num, kb_spi_polarity_t polarity)
{
	// select handler
	SPI_HandleTypeDef* handler;
	if (spi_num == SPI1)
	{
		handler = &spi_1_h_;
		__SPI1_CLK_ENABLE();
		handler->Instance = SPI1;
	}
	else if (spi_num == SPI2)
	{
		handler = &spi_2_h_;
		__SPI2_CLK_ENABLE();
		handler->Instance = SPI2;
	}
	else if (spi_num == SPI3)
	{
		handler = &spi_3_h_;
		__SPI3_CLK_ENABLE();
		handler->Instance = SPI3;
	}
	else if (spi_num == SPI4)
	{
		handler = &spi_4_h_;
		__SPI4_CLK_ENABLE();
		handler->Instance = SPI4;
	}
	else
	{
		return -1;
	}

	// basic setting
	handler->Init.Mode = SPI_MODE_MASTER;
	handler->Init.DataSize =  SPI_DATASIZE_8BIT;
	handler->Init.Direction = SPI_DIRECTION_2LINES;
	handler->Init.NSS = SPI_NSS_SOFT,			// No hardware NSS pin
	handler->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16; // TODO: generalize the frequency
	handler->Init.FirstBit = SPI_FIRSTBIT_MSB;
	handler->Init.TIMode = SPI_TIMODE_DISABLED;
	handler->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
	handler->Init.CRCPolynomial = 7;

	// polarity setting
	switch(polarity)
	{
	case LEADING_RISING_EDGE:
		handler->Init.CLKPhase = SPI_PHASE_1EDGE;
		handler->Init.CLKPolarity = SPI_POLARITY_HIGH;
		break;
	case LEADING_FALLING_EDGE:
		handler->Init.CLKPhase = SPI_PHASE_1EDGE;
		handler->Init.CLKPolarity = SPI_POLARITY_LOW;
		break;
	case TRAILING_RISING_EDGE:
		handler->Init.CLKPhase = SPI_PHASE_2EDGE;
		handler->Init.CLKPolarity = SPI_POLARITY_HIGH;
		break;
	case TRAILING_FALLING_EDGE:
		handler->Init.CLKPhase = SPI_PHASE_2EDGE;
		handler->Init.CLKPolarity = SPI_POLARITY_LOW;
		break;
	}
	return HAL_SPI_Init(handler);
}
int kb_spi_mosi_init(kb_spi_t spi_num, kb_gpio_port_t port, kb_gpio_pin_t pin)
{
	uint32_t alternate = GPIO_SPI_MOSI_AF_(spi_num, port, pin);
	if (alternate == KB_WRONG_PIN)
	{
		return -1;
	}
	kb_gpio_enable_clk(port);
	// Init GPIOs
	kb_gpio_init_t gpio_setting = {
		.Mode = GPIO_MODE_AF_PP,
		.Pull = GPIO_PULLUP,
		.Alternate = alternate,
		.Speed = GPIO_SPEED_FREQ_VERY_HIGH // 50MHz
	};
	kb_gpio_init(port, pin, &gpio_setting);
	return 0;
}

int kb_spi_miso_init(kb_spi_t spi_num, kb_gpio_port_t port, kb_gpio_pin_t pin)
{
	uint32_t alternate = GPIO_SPI_MISO_AF_(spi_num, port, pin);
	if (alternate == KB_WRONG_PIN)
	{
		return -1;
	}
	kb_gpio_enable_clk(port);
	// Init GPIOs
	kb_gpio_init_t gpio_setting = {
		.Mode = GPIO_MODE_AF_PP,
		.Pull = GPIO_PULLUP,
		.Alternate = alternate,
		.Speed = GPIO_SPEED_FREQ_VERY_HIGH // 50MHz
	};
	kb_gpio_init(port, pin, &gpio_setting);
	return 0;
}

int kb_spi_sck_init(kb_spi_t spi_num, kb_gpio_port_t port, kb_gpio_pin_t pin)
{
	uint32_t alternate = GPIO_SPI_SCK_AF_(spi_num, port, pin);
	if (alternate == KB_WRONG_PIN)
	{
		return -1;
	}
	kb_gpio_enable_clk(port);
	// Init GPIOs
	kb_gpio_init_t gpio_setting = {
		.Mode = GPIO_MODE_AF_PP,
		.Pull = GPIO_PULLUP,
		.Alternate = alternate,
		.Speed = GPIO_SPEED_FREQ_VERY_HIGH // 50MHz
	};
	kb_gpio_init(port, pin, &gpio_setting);
	return 0;
}


int kb_spi_send(kb_spi_t spi, uint8_t *buf, uint16_t size, uint32_t timeout)
{
	// select handler
	SPI_HandleTypeDef* handler;
	if (spi == SPI1)
	{
		handler = &spi_1_h_;
	}
	else if (spi == SPI2)
	{
		handler = &spi_2_h_;
	}
	else if (spi == SPI3)
	{
		handler = &spi_3_h_;
	}
	else if (spi == SPI4)
	{
		handler = &spi_4_h_;
	}
	else
	{
		return -1;
	}
	return HAL_SPI_Transmit(handler, buf, size, 0);
}
