/*
 * MODULE_HCMS-290X_DISPLAY_H_
 * HCMS-290x LED 4 Character Display driver.
 *  Created on: Sep 22, 2016
 *      Author: Bumsik Kim
 */

#ifndef _MODULE_HCMS_290X_DISPLAY_H_

#define _MODULE_HCMS_290X_DISPLAY_H_

/*
 * Pin configureation
 * DIS_RS		:PC4	When 1: Select control register, When 0: Dot register
 * 						Value of RS is latched on the falling edge of ~CE input
 * ~DIS_RESET	:PC5
 * ~DIS_CE		:PA4	When 0: enable writing, When 1: Finish Writing
 * DIS_MOSI		:PA7
 * DIS_SCK		:PA5
 */
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

#define HCMS_290X_SPI_CLK_ENABLE()		__SPI2_CLK_ENABLE()
#define HCMS_290X_RS_CLK_ENABLE()		__GPIOC_CLK_ENABLE()
#define HCMS_290X_RESET_CLK_ENABLE()	__GPIOC_CLK_ENABLE()
#define HCMS_290X_CE_CLK_ENABLE()		__GPIOA_CLK_ENABLE()
#define HCMS_290X_MOSI_CLK_ENABLE()		__GPIOC_CLK_ENABLE()
#define HCMS_290X_SCK_CLK_ENABLE()		__GPIOB_CLK_ENABLE()

#define HCMS_290X_MOSI_GPIO_MODE	GPIO_AF7_SPI2
#define HCMS_290X_SCK_GPIO_MODE		GPIO_AF5_SPI2

#ifdef __cplusplus
extern "C"{
#endif

void hcms_290x_init(void);
void hcms_290x_matrix(char *s);
void hcms_290x_clear(void);
void hcms_290x_float(float f);
void hcms_290x_int(int i);
void hcms_290x_matrix_scroll(char* str);
void hcms_290x_err(int err);

#ifdef __cplusplus
}
#endif


#endif /* _MODULE_HCMS_290X_DISPLAY_H_ */
