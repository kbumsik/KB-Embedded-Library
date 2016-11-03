/*
 * kb_TCA9545A_i2c_mux.c
 *
 *  Created on: Oct 30, 2016
 *      Author: Bumsik Kim
 */

#include "kb_TCA9545A_i2c_mux.h"
#include "kb_i2c.h"
#include "kb_gpio.h"
#include "kb_tick.h"

// base name change. Used with kb_msg(). See @kb_base.h
#ifdef KB_MSG_BASE
	#undef KB_MSG_BASE
	#define KB_MSG_BASE "TCA9545A"
#endif

#define ADDR_		(0x70U)
#define RETRY_		(10)
#define TIMEOUT_	(100)

static inline void reset_(void);

int tca9545a_init(void)
{
	volatile uint8_t buf;

	kb_gpio_init_t reset_pin_settings;
	reset_pin_settings.Mode = GPIO_MODE_OUTPUT_PP;
	reset_pin_settings.Pull = GPIO_PULLUP;
	reset_pin_settings.Speed = GPIO_SPEED_LOW;
    kb_gpio_init(TCA9545A_RESET_PORT, TCA9545A_RESET_PIN, &reset_pin_settings);

    reset_();

	/* Init I2C Bus */
	kb_i2c_init_t setting = {
			.frequency = 400000
	};
	kb_i2c_init(TCA9545A_I2C, &setting);

	/* Check the chip information */
	buf = tca9545a_current_ch();
	return 0;
}


int tca9545a_select_ch(uint8_t ch)
{
	uint8_t send;
	switch(ch)
	{
	case 0:
		send = 0x01;
		break;
	case 1:
		send = 0x02;
		break;
	case 2:
		send = 0x04;
		break;
	case 3:
		send = 0x08;
		break;
	default:
		kb_error("Wrong channel\r\n");
		return -1;
	}
	while (KB_OK != kb_i2c_send_timeout(TCA9545A_I2C, ADDR_, &send, 1, TIMEOUT_))
	{
		kb_error("TCA9545 not found! retry\n");
		if (0 == tca9545a_init())
		{
			continue;
		}
		return -1;
	}
	/* FIXME: Delay needed, but what is the minimum? */
	kb_delay_us(100);
	return 0;
}


uint8_t tca9545a_current_ch(void)
{
	uint8_t buf = 0;
	uint8_t retry = 0;
	while (KB_OK != kb_i2c_receive_timeout(TCA9545A_I2C, ADDR_, &buf, 1, TIMEOUT_))
	{
		retry++;
		if (retry > RETRY_)
		{
			kb_error("Failed to connect TCA9545!\n");
			return 0;
		}
		kb_error("TCA9545A not found! retry\n");
		reset_();
	}
	return	buf;
}


static inline void reset_(void)
{
	kb_gpio_set(TCA9545A_RESET_PORT, TCA9545A_RESET_PIN, GPIO_PIN_RESET);
	kb_delay_ms(1);
	kb_gpio_set(TCA9545A_RESET_PORT, TCA9545A_RESET_PIN, GPIO_PIN_SET);
}
