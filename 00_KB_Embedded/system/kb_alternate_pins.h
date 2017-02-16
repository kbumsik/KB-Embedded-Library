/*
 * kb_alternate_pins.h
 *
 *  Created on: Oct 25, 2016
 *      Author: Bumsik Kim
 */

#ifndef BSP_STM32F446XX_NUCLEO64_KB_ALTERNATE_PINS_H_
#define BSP_STM32F446XX_NUCLEO64_KB_ALTERNATE_PINS_H_

#include "kb_config.h"

#define KB_WRONG_PIN	0xFFU

// Check MCU
#if !defined(STM32F446xx)
	#error "Please define proper MCU! Otherwise KB_LIB will set incorrect pins!"
#endif

/******************************************************************************
 ****************************** STM32F446xx ***********************************
 ******************************************************************************/
#if defined(STM32F446xx)
/******************************************************************************
 * SPI
 ******************************************************************************/

// Select alternate mode functions
// Don't care about GPIO_AF5_SPI'2' <-- the SPI number. They are the same value.
#define GPIO_SPI_MISO_AF_(spi, pin) (\
							IS_SPI_MISO_AF5_(spi, pin)?GPIO_AF5_SPI2: \
							IS_SPI_MISO_AF6_(spi, pin)?GPIO_AF6_SPI2: \
							IS_SPI_MISO_AF7_(spi, pin)?GPIO_AF7_SPI2: \
							KB_WRONG_PIN)

#define GPIO_SPI_MOSI_AF_(spi, pin) (\
							IS_SPI_MOSI_AF5_(spi, pin)?GPIO_AF5_SPI2: \
							IS_SPI_MOSI_AF6_(spi, pin)?GPIO_AF6_SPI2: \
							IS_SPI_MOSI_AF7_(spi, pin)?GPIO_AF7_SPI2: \
							KB_WRONG_PIN)

#define GPIO_SPI_SCK_AF_(spi, pin) (\
							IS_SPI_SCK_AF5_(spi, pin)?GPIO_AF5_SPI2: \
							IS_SPI_SCK_AF6_(spi, pin)?GPIO_AF6_SPI2: \
							IS_SPI_SCK_AF7_(spi, pin)?GPIO_AF7_SPI2: \
							KB_WRONG_PIN)

#define GPIO_SPI_NSS_AF_(spi, pin) (\
							IS_SPI_NSS_AF5_(spi, pin)?GPIO_AF5_SPI2: \
							IS_SPI_NSS_AF6_(spi, pin)?GPIO_AF6_SPI2: \
							IS_SPI_NSS_AF7_(spi, pin)?GPIO_AF7_SPI2: \
							KB_WRONG_PIN)

// AF5
#define IS_SPI_MISO_AF5_(spi, pin) (\
							((spi == SPI1) && ( \
							(pin == PA_6)|| \
							(pin == PB_4))) \
							|| ((spi == SPI2) && ( \
							(pin == PB_14)|| \
							(pin == PC_2))) \
							|| ((spi == SPI4) && ( \
							(pin == PD_0)|| \
							(pin == PE_5)|| \
							(pin == PE_13))) \
							)

#define IS_SPI_MOSI_AF5_(spi, pin) (\
							((spi == SPI1) && ( \
							(pin == PA_7)|| \
							(pin == PB_5))) \
							|| ((spi == SPI2) && ( \
							(pin == PB_15)|| \
							(pin == PC_3))) \
							|| ((spi == SPI3) && ( \
							(pin == PC_1)|| \
							(pin == PD_6))) \
							|| ((spi == SPI4) && ( \
							(pin == PE_6)|| \
							(pin == PE_14))) \
							)

#define IS_SPI_SCK_AF5_(spi, pin) (\
							((spi == SPI1) && ( \
							(pin == PA_5)|| \
							(pin == PB_3))) \
							|| ((spi == SPI2) && ( \
							(pin == PA_9)|| \
							(pin == PB_10)|| \
							(pin == PB_13)|| \
							(pin == PC_7)|| \
							(pin == PD_3))) \
							|| ((spi == SPI4) && ( \
							(pin == PE_2)|| \
							(pin == PE_12))) \
							)

#define IS_SPI_NSS_AF5_(spi, pin) (\
							((spi == SPI1) && ( \
							(pin == PA_4)|| \
							(pin == PA_15))) \
							|| ((spi == SPI2) && ( \
							(pin == PB_9)|| \
							(pin == PB_12))) \
							|| ((spi == SPI4) && ( \
							(pin == PE_4)|| \
							(pin == PE_11))) \
							)

// AF6
#define IS_SPI_MISO_AF6_(spi, pin) (\
							((spi == SPI3) && ( \
							(pin == PB_4)|| \
							(pin == PC_11))) \
							|| ((spi == SPI4) && ( \
							(pin == PG_12))) \
							)

#define IS_SPI_MOSI_AF6_(spi, pin) (\
							((spi == SPI3) && ( \
							(pin == PB_5)|| \
							(pin == PC_12)|| \
							(pin == PD_0))) \
							|| ((spi == SPI4) && ( \
							(pin == PG_13)))\
							)

#define IS_SPI_SCK_AF6_(spi, pin) (\
							((spi == SPI3) && ( \
							(pin == PB_3)|| \
							(pin == PC_10)))\
							|| ((spi == SPI4) && ( \
							(pin == PG_11))) \
							)

#define IS_SPI_NSS_AF6_(spi, pin) (\
							((spi == SPI3) && ( \
							(pin == PA_4)|| \
							(pin == PA_15))) \
							|| ((spi == SPI4) && ( \
							(pin == PG_14))) \
							)

// AF7
#define IS_SPI_MISO_AF7_(spi, pin)	(0)

#define IS_SPI_MOSI_AF7_(spi, pin) (\
							((spi == SPI2) && ( \
							(pin == PC_1))) \
							|| ((spi == SPI3) && ( \
							(pin == PB_0)|| \
							(pin == PB_2))) \
							)

#define IS_SPI_SCK_AF7_(spi, pin) (0)

#define IS_SPI_NSS_AF7_(spi, pin) (\
							((spi == SPI2) && ( \
							(pin == PB_4)|| \
							(pin == PD_1))) \
							)


/******************************************************************************
 * UART
 ******************************************************************************/
// Select alternate mode functions
// Don't care about GPIO_AF7_USART'5' <-- the SPI number. They are the same value.
#define GPIO_USART_TX_AF_(usart, pin) (\
							IS_USART_TX_AF7_(usart, pin)?GPIO_AF7_UART5: \
							IS_USART_TX_AF8_(usart, pin)?GPIO_AF8_UART5: \
							KB_WRONG_PIN)

#define GPIO_USART_RX_AF_(usart, pin) (\
							IS_USART_RX_AF7_(usart, pin)?GPIO_AF7_UART5: \
							IS_USART_RX_AF8_(usart, pin)?GPIO_AF8_UART5: \
							KB_WRONG_PIN)

// AF7
#define IS_USART_TX_AF7_(usart, pin) (\
							((usart == USART1) && ( \
							(pin == PA_9)|| \
							(pin == PB_6))) \
							|| ((usart == USART2) && ( \
							(pin == PA_2)|| \
							(pin == PD_5))) \
							|| ((usart == USART3) && ( \
							(pin == PB_10)|| \
							(pin == PC_10)|| \
							(pin == PD_8))) \
							)

#define IS_USART_RX_AF7_(usart, pin) (\
							((usart == USART1) && ( \
							(pin == PA_10)|| \
							(pin == PB_7))) \
							|| ((usart == USART2) && ( \
							(pin == PA_3)|| \
							(pin == PD_6))) \
							|| ((usart == USART3) && ( \
							(pin == PB_11)|| \
							(pin == PC_5)|| \
							(pin == PC_11)|| \
							(pin == PD_9))) \
							)

// AF8
#define IS_USART_TX_AF8_(usart, pin) (\
							((usart == UART4) && ( \
							(pin == PA_0)|| \
							(pin == PC_10))) \
							|| ((usart == UART5) && ( \
							(pin == PC_12)|| \
							(pin == PE_8))) \
							|| ((usart == USART6) && ( \
							(pin == PC_6)|| \
							(pin == PG_14))) \
							)

#define IS_USART_RX_AF8_(usart, pin) (\
							((usart == UART4) && ( \
							(pin == PA_1)|| \
							(pin == PC_11))) \
							|| ((usart == UART5) && ( \
							(pin == PD_2)|| \
							(pin == PE_7))) \
							|| ((usart == USART6) && ( \
							(pin == PC_7)|| \
							(pin == PG_9))) \
							)


/******************************************************************************
 * TIM
 ******************************************************************************/
// Select alternate mode functions
// Don't care about GPIO_AF7_USART'5' <-- the SPI number. They are the same value.
#define GPIO_TIM_CH1_AF_(timer, pin) (\
							IS_TIM_CH1_AF1_(timer, pin)?GPIO_AF1_TIM1: \
							IS_TIM_CH1_AF2_(timer, pin)?GPIO_AF2_TIM3: \
							IS_TIM_CH1_AF3_(timer, pin)?GPIO_AF3_TIM8: \
							IS_TIM_CH1_AF9_(timer, pin)?GPIO_AF9_TIM12: \
							KB_WRONG_PIN)

#define GPIO_TIM_CH2_AF_(timer, pin) (\
							IS_TIM_CH2_AF1_(timer, pin)?GPIO_AF1_TIM1: \
							IS_TIM_CH2_AF2_(timer, pin)?GPIO_AF2_TIM3: \
							IS_TIM_CH2_AF3_(timer, pin)?GPIO_AF3_TIM8: \
							IS_TIM_CH2_AF9_(timer, pin)?GPIO_AF9_TIM12: \
							KB_WRONG_PIN)
#define GPIO_TIM_CH3_AF_(timer, pin) (\
							IS_TIM_CH3_AF1_(timer, pin)?GPIO_AF1_TIM1: \
							IS_TIM_CH3_AF2_(timer, pin)?GPIO_AF2_TIM3: \
							IS_TIM_CH3_AF3_(timer, pin)?GPIO_AF3_TIM8: \
							IS_TIM_CH3_AF9_(timer, pin)?GPIO_AF9_TIM12: \
							KB_WRONG_PIN)

#define GPIO_TIM_CH4_AF_(timer, pin) (\
							IS_TIM_CH4_AF1_(timer, pin)?GPIO_AF1_TIM1: \
							IS_TIM_CH4_AF2_(timer, pin)?GPIO_AF2_TIM3: \
							IS_TIM_CH4_AF3_(timer, pin)?GPIO_AF3_TIM8: \
							IS_TIM_CH4_AF9_(timer, pin)?GPIO_AF9_TIM12: \
							KB_WRONG_PIN)

// AF1
#define IS_TIM_CH1_AF1_(timer, pin) (\
							((timer == TIM1) && ( \
							(pin == PA_8)|| \
							(pin == PE_9))) \
							|| ((timer == TIM2) && ( \
							(pin == PA_0)|| \
							(pin == PA_5)|| \
							(pin == PA_15)|| \
							(pin == PB_8))) \
							)

#define IS_TIM_CH2_AF1_(timer, pin) (\
							((timer == TIM1) && ( \
							(pin == PA_9)|| \
							(pin == PE_11))) \
							|| ((timer == TIM2) && ( \
							(pin == PA_1)|| \
							(pin == PB_3)|| \
							(pin == PB_9))) \
							)

#define IS_TIM_CH3_AF1_(timer, pin) (\
							((timer == TIM1) && ( \
							(pin == PA_10)|| \
							(pin == PE_13))) \
							|| ((timer == TIM2) && ( \
							(pin == PA_2)|| \
							(pin == PB_10))) \
							)

#define IS_TIM_CH4_AF1_(timer, pin) (\
							((timer == TIM1) && ( \
							(pin == PA_11)|| \
							(pin == PE_14))) \
							|| ((timer == TIM2) && ( \
							(pin == PA_4)|| \
							(pin == PB_2)|| \
							(pin == PB_11))) \
							)

// AF2
#define IS_TIM_CH1_AF2_(timer, pin) (\
							((timer == TIM3) && ( \
							(pin == PA_6)|| \
							(pin == PB_4)|| \
							(pin == PC_6))) \
							|| ((timer == TIM4) && ( \
							(pin == PB_6)|| \
							(pin == PD_12))) \
							|| ((timer == TIM5) && ( \
							(pin == PA_0))) \
							)

#define IS_TIM_CH2_AF2_(timer, pin) (\
							((timer == TIM3) && ( \
							(pin == PA_7)|| \
							(pin == PB_5)|| \
							(pin == PC_7))) \
							|| ((timer == TIM4) && ( \
							(pin == PB_7)|| \
							(pin == PD_13))) \
							|| ((timer == TIM5) && ( \
							(pin == PA_1))) \
							)

#define IS_TIM_CH3_AF2_(timer, pin) (\
							((timer == TIM3) && ( \
							(pin == PB_0)|| \
							(pin == PC_8))) \
							|| ((timer == TIM4) && ( \
							(pin == PB_8)|| \
							(pin == PD_14))) \
							|| ((timer == TIM5) && ( \
							(pin == PA_2))) \
							)

#define IS_TIM_CH4_AF2_(timer, pin) (\
							((timer == TIM3) && ( \
							(pin == PB_1)|| \
							(pin == PC_9))) \
							|| ((timer == TIM4) && ( \
							(pin == PB_9)|| \
							(pin == PD_15))) \
							|| ((timer == TIM5) && ( \
							(pin == PA_3))) \
							)

// AF3
#define IS_TIM_CH1_AF3_(timer, pin) (\
							((timer == TIM8) && ( \
							(pin == PC_6))) \
							|| ((timer == TIM9) && ( \
							(pin == PA_2)|| \
							(pin == PE_5))) \
							|| ((timer == TIM10) && ( \
							(pin == PB_8)|| \
							(pin == PF_6))) \
							|| ((timer == TIM11) && ( \
							(pin == PB_9)|| \
							(pin == PF_7))) \
							)

#define IS_TIM_CH2_AF3_(timer, pin) (\
							((timer == TIM8) && ( \
							(pin == PC_7))) \
							|| ((timer == TIM9) && ( \
							(pin == PA_3)|| \
							(pin == PE_6))) \
							)

#define IS_TIM_CH3_AF3_(timer, pin) (\
							((timer == TIM8) && ( \
							(pin == PC_8))) \
							)

#define IS_TIM_CH4_AF3_(timer, pin) (\
							((timer == TIM8) && ( \
							(pin == PC_9))) \
							)

// AF9
#define IS_TIM_CH1_AF9_(timer, pin) (\
							((timer == TIM12) && ( \
							(pin == PB_4))) \
							|| ((timer == TIM13) && ( \
							(pin == PA_6)|| \
							(pin == PF_8))) \
							|| ((timer == TIM14) && ( \
							(pin == PA_7)|| \
							(pin == PF_9))) \
							)

#define IS_TIM_CH2_AF9_(timer, pin) (\
							((timer == TIM12) && ( \
							(pin == PB_5))) \
							)

#define IS_TIM_CH3_AF9_(timer, pin) (0)

#define IS_TIM_CH4_AF9_(timer, pin) (0)

/******************************************************************************
 * I2C
 ******************************************************************************/
// Select alternate mode functions
// Don't care about GPIO_AF7_USART'5' <-- the SPI number. They are the same value.
#define GPIO_I2C_SCL_AF_(i2c, pin) (\
							IS_I2C_SCL_AF4_(i2c, pin)?GPIO_AF4_I2C1: \
							KB_WRONG_PIN)

#define GPIO_I2C_SDA_AF_(i2c, pin) (\
							IS_I2C_SDA_AF4_(i2c, pin)?GPIO_AF4_I2C1: \
							KB_WRONG_PIN)

// AF7
#define IS_I2C_SCL_AF4_(i2c, pin) (\
							((i2c == I2C1) && ( \
							(pin == PB_6)|| \
							(pin == PB_8))) \
							|| ((i2c == I2C2) && ( \
							(pin == PB_10)|| \
							(pin == PF_1))) \
							|| ((i2c == I2C3) && ( \
							(pin == PA_8))) \
							)

#define IS_I2C_SDA_AF4_(i2c, pin) (\
							((i2c == I2C1) && ( \
							(pin == PB_7)|| \
							(pin == PB_9))) \
							|| ((i2c == I2C2) && ( \
							(pin == PB_3)|| \
							(pin == PB_11)|| \
							(pin == PC_12)|| \
							(pin == PF_0))) \
							|| ((i2c == I2C3) && ( \
							(pin == PB_4)|| \
							(pin == PC_9))) \
							)


/******************************************************************************
 ****************************** STM32F407xx ***********************************
 ******************************************************************************/
#elif defined(STM32F407xx)
#endif

#endif /* BSP_STM32F446XX_NUCLEO64_KB_ALTERNATE_PINS_H_ */
