#include "kb_tick.h"
#include "main.h"
// KB library
#include "system_config.h"
#include "trace.h"
#include "kb_gpio.h"
#include "kb_HCMS-290X_display.h"
#include "kb_terminal.h"

int main(void)
{
	// initialize clock and system configuration
    system_init();

    // Initialize all configured peripherals
    peripheral_init();

    // init peripherals for the LED display
    hcms_290x_init();

    hcms_290x_matrix("STRT");
    kb_gpio_toggle(LED1_GPIO_Port, LED1_Pin);
    kb_delay_ms(500);
    kb_gpio_toggle(LED1_GPIO_Port, LED1_Pin);
    trace_puts("Hello ARM World!");
    kb_terminal_puts("Hello World!\r\n");
    uint32_t seconds = 0;
    while (1)
    {
    	kb_gpio_toggle(LED1_GPIO_Port, LED1_Pin);
    	kb_delay_us(1000000);

        ++seconds;
        // Count seconds on the trace device.
        trace_printf("Second %u\n", seconds);
        kb_terminal_puts("Blink!\r\n");
        hcms_290x_int(seconds);
    }
}
