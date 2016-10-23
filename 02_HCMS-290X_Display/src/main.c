#include "main.h"
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "system_config.h"
#include "trace.h"
#include "kb_timer.h"
#include "HCMS-290X_display.h"

int main(void)
{
	// initialize clock and system configuration
    system_init();

    // Initialize all configured peripherals
    peripheral_init();

    // init peripherals for the LED display
    hcms_290x_init();
    hcms_290x_clear();

    hcms_290x_matrix("STR ");
    HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
    kb_timer_delay_ms(500);
    HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
    trace_puts("Hello ARM World!");
    uint32_t seconds = 0;
    while (1)
    {
    	HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
    	kb_timer_delay_us(1000000);

        ++seconds;
        // Count seconds on the trace device.
        trace_printf("Second %u\n", seconds);
        hcms_290x_int(seconds);
    }
}
