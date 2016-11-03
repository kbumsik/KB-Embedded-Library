/*
 * kb_TCA9545A_i2c_mux.h
 *
 *  Created on: Oct 30, 2016
 *      Author: Bumsik Kim
 */

#ifndef MODULE_KB_TCA9545A_I2C_MUX_H_
#define MODULE_KB_TCA9545A_I2C_MUX_H_


#include "kb_base.h"
#include "kb_module_config.h"

#ifndef TCA9545A_I2C
	#define TCA9545A_I2C		I2C1
	#define TCA9545A_SDA_PORT	GPIOB
	#define TCA9545A_SDA_PIN	GPIO_PIN_9
	#define TCA9545A_SCL_PORT	GPIOB
	#define TCA9545A_SCL_PIN	GPIO_PIN_8
	#define TCA9545A_RESET_PORT	GPIOC
	#define TCA9545A_RESET_PIN	GPIO_PIN_13
#endif

#ifdef __cplusplus
extern "C"{
#endif

int tca9545a_init(void);
int tca9545a_select_ch(uint8_t ch);
uint8_t tca9545a_current_ch(void);

#ifdef __cplusplus
}
#endif


#endif /* MODULE_KB_TCA9545A_I2C_MUX_H_ */
