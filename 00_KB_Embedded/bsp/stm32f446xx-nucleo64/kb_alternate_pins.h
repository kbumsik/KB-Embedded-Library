/*
 * kb_alternate_pins.h
 *
 *  Created on: Oct 25, 2016
 *      Author: Bumsik Kim
 */

#ifndef BSP_STM32F446XX_NUCLEO64_KB_ALTERNATE_PINS_H_
#define BSP_STM32F446XX_NUCLEO64_KB_ALTERNATE_PINS_H_

#include "stm32f4xx.h"

#define KB_WRONG_PIN	0xFFU

/******************************************************************************
 * SPI
 ******************************************************************************/

// Select alternate mode functions
// Don't care about GPIO_AF5_SPI'2' <-- the SPI number. They are the same value.
#define GPIO_SPI_MISO_AF_(spi, port, pin) (\
							IS_SPI_MISO_AF5_(spi, port, pin)?GPIO_AF5_SPI2: \
							IS_SPI_MISO_AF6_(spi, port, pin)?GPIO_AF6_SPI2: \
							IS_SPI_MISO_AF7_(spi, port, pin)?GPIO_AF7_SPI2: \
							KB_WRONG_PIN)

#define GPIO_SPI_MOSI_AF_(spi, port, pin) (\
							IS_SPI_MOSI_AF5_(spi, port, pin)?GPIO_AF5_SPI2: \
							IS_SPI_MOSI_AF6_(spi, port, pin)?GPIO_AF6_SPI2: \
							IS_SPI_MOSI_AF7_(spi, port, pin)?GPIO_AF7_SPI2: \
							KB_WRONG_PIN)

#define GPIO_SPI_SCK_AF_(spi, port, pin) (\
							IS_SPI_SCK_AF5_(spi, port, pin)?GPIO_AF5_SPI2: \
							IS_SPI_SCK_AF6_(spi, port, pin)?GPIO_AF6_SPI2: \
							IS_SPI_SCK_AF7_(spi, port, pin)?GPIO_AF7_SPI2: \
							KB_WRONG_PIN)

#define GPIO_SPI_NSS_AF_(spi, port, pin) (\
							IS_SPI_NSS_AF5_(spi, port, pin)?GPIO_AF5_SPI2: \
							IS_SPI_NSS_AF6_(spi, port, pin)?GPIO_AF6_SPI2: \
							IS_SPI_NSS_AF7_(spi, port, pin)?GPIO_AF7_SPI2: \
							KB_WRONG_PIN)


// AF5
#define IS_SPI_MISO_AF5_(spi, port, pin) (\
							((spi == SPI1) && ( \
							(port == GPIOA && pin == GPIO_PIN_6)|| \
							(port == GPIOB && pin == GPIO_PIN_4))) \
							|| ((spi == SPI2) && ( \
							(port == GPIOB && pin == GPIO_PIN_14)|| \
							(port == GPIOC && pin == GPIO_PIN_2))) \
							|| ((spi == SPI4) && ( \
							(port == GPIOD && pin == GPIO_PIN_0)|| \
							(port == GPIOE && pin == GPIO_PIN_5)|| \
							(port == GPIOE && pin == GPIO_PIN_13))) \
							)

#define IS_SPI_MOSI_AF5_(spi, port, pin) (\
							((spi == SPI1) && ( \
							(port == GPIOA && pin == GPIO_PIN_7)|| \
							(port == GPIOB && pin == GPIO_PIN_5))) \
							|| ((spi == SPI2) && ( \
							(port == GPIOB && pin == GPIO_PIN_15)|| \
							(port == GPIOC && pin == GPIO_PIN_3))) \
							|| ((spi == SPI3) && ( \
							(port == GPIOC && pin == GPIO_PIN_1)|| \
							(port == GPIOD && pin == GPIO_PIN_6))) \
							|| ((spi == SPI4) && ( \
							(port == GPIOE && pin == GPIO_PIN_6)|| \
							(port == GPIOE && pin == GPIO_PIN_14))) \
							)

#define IS_SPI_SCK_AF5_(spi, port, pin) (\
							((spi == SPI1) && ( \
							(port == GPIOA && pin == GPIO_PIN_5)|| \
							(port == GPIOB && pin == GPIO_PIN_3))) \
							|| ((spi == SPI2) && ( \
							(port == GPIOA && pin == GPIO_PIN_9)|| \
							(port == GPIOB && pin == GPIO_PIN_10)|| \
							(port == GPIOB && pin == GPIO_PIN_13)|| \
							(port == GPIOC && pin == GPIO_PIN_7)|| \
							(port == GPIOD && pin == GPIO_PIN_3))) \
							|| ((spi == SPI4) && ( \
							(port == GPIOE && pin == GPIO_PIN_2)|| \
							(port == GPIOE && pin == GPIO_PIN_12))) \
							)

#define IS_SPI_NSS_AF5_(spi, port, pin) (\
							((spi == SPI1) && ( \
							(port == GPIOA && pin == GPIO_PIN_4)|| \
							(port == GPIOA && pin == GPIO_PIN_15))) \
							|| ((spi == SPI2) && ( \
							(port == GPIOB && pin == GPIO_PIN_9)|| \
							(port == GPIOB && pin == GPIO_PIN_12))) \
							|| ((spi == SPI4) && ( \
							(port == GPIOE && pin == GPIO_PIN_4)|| \
							(port == GPIOE && pin == GPIO_PIN_11))) \
							)


// AF6
#define IS_SPI_MISO_AF6_(spi, port, pin) (\
							((spi == SPI3) && ( \
							(port == GPIOB && pin == GPIO_PIN_4)|| \
							(port == GPIOC && pin == GPIO_PIN_11))) \
							|| ((spi == SPI4) && ( \
							(port == GPIOG && pin == GPIO_PIN_12))) \
							)

#define IS_SPI_MOSI_AF6_(spi, port, pin) (\
							((spi == SPI3) && ( \
							(port == GPIOB && pin == GPIO_PIN_5)|| \
							(port == GPIOC && pin == GPIO_PIN_12)|| \
							(port == GPIOD && pin == GPIO_PIN_0))) \
							|| ((spi == SPI4) && ( \
							(port == GPIOG && pin == GPIO_PIN_13)))\
							)

#define IS_SPI_SCK_AF6_(spi, port, pin) (\
							((spi == SPI3) && ( \
							(port == GPIOB && pin == GPIO_PIN_3)|| \
							(port == GPIOC && pin == GPIO_PIN_10)))\
							|| ((spi == SPI4) && ( \
							(port == GPIOG && pin == GPIO_PIN_11))) \
							)

#define IS_SPI_NSS_AF6_(spi, port, pin) (\
							((spi == SPI3) && ( \
							(port == GPIOA && pin == GPIO_PIN_4)|| \
							(port == GPIOA && pin == GPIO_PIN_15))) \
							|| ((spi == SPI4) && ( \
							(port == GPIOG && pin == GPIO_PIN_14))) \
							)





// AF7
#define IS_SPI_MISO_AF7_(spi, port, pin)	(0)

#define IS_SPI_MOSI_AF7_(spi, port, pin) (\
							((spi == SPI2) && ( \
							(port == GPIOC && pin == GPIO_PIN_1))) \
							|| ((spi == SPI3) && ( \
							(port == GPIOB && pin == GPIO_PIN_0)|| \
							(port == GPIOB && pin == GPIO_PIN_2))) \
							)

#define IS_SPI_SCK_AF7_(spi, port, pin) (0)

#define IS_SPI_NSS_AF7_(spi, port, pin) (\
							((spi == SPI2) && ( \
							(port == GPIOB && pin == GPIO_PIN_4)|| \
							(port == GPIOD && pin == GPIO_PIN_1))) \
							)


/******************************************************************************
 * UART
 ******************************************************************************/
// AF7
// Select alternate mode functions
// Don't care about GPIO_AF7_USART'5' <-- the SPI number. They are the same value.
#define GPIO_USART_TX_AF_(usart, port, pin) (\
							IS_USART_TX_AF7_(usart, port, pin)?GPIO_AF7_UART5: \
							IS_USART_TX_AF8_(usart, port, pin)?GPIO_AF8_UART5: \
							KB_WRONG_PIN)

#define GPIO_USART_RX_AF_(usart, port, pin) (\
							IS_USART_RX_AF7_(usart, port, pin)?GPIO_AF7_UART5: \
							IS_USART_RX_AF8_(usart, port, pin)?GPIO_AF8_UART5: \
							KB_WRONG_PIN)

// AF7
#define IS_USART_TX_AF7_(usart, port, pin) (\
							((usart == USART1) && ( \
							(port == GPIOA && pin == GPIO_PIN_9)|| \
							(port == GPIOB && pin == GPIO_PIN_6))) \
							|| ((usart == USART2) && ( \
							(port == GPIOA && pin == GPIO_PIN_2)|| \
							(port == GPIOD && pin == GPIO_PIN_5))) \
							|| ((usart == USART3) && ( \
							(port == GPIOB && pin == GPIO_PIN_10)|| \
							(port == GPIOC && pin == GPIO_PIN_10)|| \
							(port == GPIOD && pin == GPIO_PIN_8))) \
							)

#define IS_USART_RX_AF7_(usart, port, pin) (\
							((usart == USART1) && ( \
							(port == GPIOA && pin == GPIO_PIN_10)|| \
							(port == GPIOB && pin == GPIO_PIN_7))) \
							|| ((usart == USART2) && ( \
							(port == GPIOA && pin == GPIO_PIN_3)|| \
							(port == GPIOD && pin == GPIO_PIN_6))) \
							|| ((usart == USART3) && ( \
							(port == GPIOB && pin == GPIO_PIN_11)|| \
							(port == GPIOC && pin == GPIO_PIN_5)|| \
							(port == GPIOC && pin == GPIO_PIN_11)|| \
							(port == GPIOD && pin == GPIO_PIN_9))) \
							)

// AF8
#define IS_USART_TX_AF8_(usart, port, pin) (\
							((usart == UART4) && ( \
							(port == GPIOA && pin == GPIO_PIN_0)|| \
							(port == GPIOC && pin == GPIO_PIN_10))) \
							|| ((usart == UART5) && ( \
							(port == GPIOC && pin == GPIO_PIN_12)|| \
							(port == GPIOE && pin == GPIO_PIN_8))) \
							|| ((usart == USART6) && ( \
							(port == GPIOC && pin == GPIO_PIN_6)|| \
							(port == GPIOG && pin == GPIO_PIN_14))) \
							)

#define IS_USART_RX_AF8_(usart, port, pin) (\
							((usart == UART4) && ( \
							(port == GPIOA && pin == GPIO_PIN_1)|| \
							(port == GPIOC && pin == GPIO_PIN_11))) \
							|| ((usart == UART5) && ( \
							(port == GPIOD && pin == GPIO_PIN_2)|| \
							(port == GPIOE && pin == GPIO_PIN_7))) \
							|| ((usart == USART6) && ( \
							(port == GPIOC && pin == GPIO_PIN_7)|| \
							(port == GPIOG && pin == GPIO_PIN_9))) \
							)


#endif /* BSP_STM32F446XX_NUCLEO64_KB_ALTERNATE_PINS_H_ */
