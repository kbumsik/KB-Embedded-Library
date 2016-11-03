/*
 * kb_base.h
 *
 *  Created on: Oct 27, 2016
 *      Author: Bumsik Kim
 */

#ifndef SYSTEM_KB_BASE_H_
#define SYSTEM_KB_BASE_H_


// base library setting
#if defined(USE_HAL_DRIVER)
	#if defined(STM32F446xx) || defined(STM32F407xx)
		#include "stm32f4xx.h"
		#include "stm32f4xx_hal_def.h" // TODO: port this to our library
		// #define STM32F4 -- already defined in "stm32f4xx"
		#define STM32
	#endif
#else
	#error "Please define device library!!"
#endif

// library message printing
#ifdef DEBUG
	#if defined(DEBUG_TO_TERMINAL)
		#include "kb_terminal.h"
		#define KB_MSG_BASE	"UNKOWN"
		#define kb_msg(msg, ...)	kb_terminal_printf("KB_LIB:" KB_MSG_BASE ":%d:" msg, __LINE__ ,##__VA_ARGS__)
		#define kb_warning(msg, ...)	kb_terminal_printf("KB_LIB:" KB_MSG_BASE ":%d:Warning:" msg, __LINE__ , ##__VA_ARGS__)
		#define kb_error(msg, ...)	kb_terminal_printf("KB_LIB:" KB_MSG_BASE ":%d:Error: " msg, __LINE__ , ##__VA_ARGS__)
	#elif defined(DEBUG_TO_SEMIHOSTING)
		#include "trace.h"
		#define kb_msg(msg, ...)	trace_printf("KB_LIB:" KB_MSG_BASE ":%d:" msg, __LINE__ , ##__VA_ARGS__)
		#define kb_warning(msg, ...)	trace_printf("KB_LIB:" KB_MSG_BASE ":%d:Warning:" msg, __LINE__ , ##__VA_ARGS__)
		#define kb_error(msg, ...)	trace_printf("KB_LIB:" KB_MSG_BASE ":%d:Error: " msg, __LINE__ , ##__VA_ARGS__)
	#else
		#include "trace.h"
		#define kb_msg(msg, ...)	trace_printf("KB_LIB:" KB_MSG_BASE ":%d:" msg, __LINE__ , ##__VA_ARGS__)
		#define kb_warning(msg, ...)	trace_printf("KB_LIB:" KB_MSG_BASE ":%d:Warning:" msg, __LINE__ , ##__VA_ARGS__)
		#define kb_error(msg, ...)	trace_printf("KB_LIB:" KB_MSG_BASE ":%d:Error: " msg, __LINE__ , ##__VA_ARGS__)
	#endif
#else
	#define kb_msg(msg, ...)
	#define kb_warning(msg, ...)
	#define kb_error(msg, ...)
#endif

// library status return setting
#if defined(STM32F4)
	typedef enum {
		KB_OK = HAL_OK,
		KB_ERROR = HAL_ERROR,
		KB_BUSY = HAL_BUSY,
		KB_TIMEOUT = HAL_TIMEOUT
	} kb_status_t;
	#define TIMEOUT_MAX		HAL_MAX_DELAY
#else
#endif

#endif /* SYSTEM_KB_BASE_H_ */
