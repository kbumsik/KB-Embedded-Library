/*
 * kb_spi.c
 *
 *  Created on: Oct 25, 2016
 *      Author: Bumsik Kim
 */

#include "kb_common_source.h"
#include "kb_spi.h"
#include "kb_alternate_pins.h"

// base name change. Used with kb_msg(). See @kb_base.h
#ifdef KB_MSG_BASE
    #undef KB_MSG_BASE
    #define KB_MSG_BASE "SPI"
#endif

static uint32_t _get_bus_freq(kb_spi_t spi);
static SPI_HandleTypeDef * _get_handler (kb_spi_t spi);
static void _enable_spi_clk (kb_spi_t spi);

// forward declaration of constant variables
struct _prescaler {
    uint32_t	divisor;
    uint32_t divisor_macro;
};
static const uint8_t _ps_table_size;
static const struct _prescaler _ps_table[];

/******************************************************************************
 * Function definitions
 ******************************************************************************/

int kb_spi_init(kb_spi_t spi, kb_spi_init_t *settings)
{
    // select handler
    SPI_HandleTypeDef* handler = _get_handler(spi);
    if (NULL == handler) {
        return KB_ERROR;
    }
    _enable_spi_clk(spi);

    // basic setting
    handler->Init.Mode = SPI_MODE_MASTER;
    handler->Init.DataSize =  SPI_DATASIZE_8BIT;
    handler->Init.Direction = SPI_DIRECTION_2LINES;
    handler->Init.NSS = SPI_NSS_SOFT,			// No hardware NSS pin
    handler->Init.FirstBit = SPI_FIRSTBIT_MSB;
    handler->Init.TIMode = SPI_TIMODE_DISABLED;
    handler->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
    handler->Init.CRCPolynomial = 7;

    // frequency setting
    // use binary search
    uint32_t freq_bus = _get_bus_freq(spi);
    uint32_t ps_target = freq_bus/settings->frequency;
    uint8_t front = _ps_table_size - 1;
    uint8_t back = 0;
    uint8_t ps_idx;
    uint32_t ps_matched;
    uint32_t ps_behind;
    // Check boundary frequency first
    if(ps_target > _ps_table[front -1].divisor) {
        ps_idx = front;
        ps_matched = _ps_table[ps_idx].divisor;
        KB_DEBUG_WARNING("Prescaler is touching its border vale\r\n");
        KB_DEBUG_WARNING("	You might want to double check\r\n");
    } else if (ps_target <= _ps_table[0].divisor) {
        ps_idx = 0;
        ps_matched = _ps_table[ps_idx].divisor;
        KB_DEBUG_WARNING("Prescaler is touching its border value");
        KB_DEBUG_WARNING("	You might want to double check\r\n");
    } else {
        // start binary search
        while(1) {
            ps_idx = (front+back)/2;
            ps_matched = _ps_table[ps_idx].divisor;
            ps_behind = _ps_table[ps_idx - 1].divisor;
            if(ps_matched < ps_target) {
                back = ps_idx;
            } else if (ps_behind < ps_target) {
                break;
            } else {
                front = ps_idx;
            }
        }
    }
    KB_DEBUG_MSG("requested frequency :%lu\r\n", (unsigned long int)settings->frequency);
    KB_DEBUG_MSG("selected divisor is %u\r\n", (unsigned int)_ps_table[ps_idx].divisor);
    KB_DEBUG_MSG("selected frequency is %lu\r\n", (unsigned long int)freq_bus/ps_matched);

    handler->Init.BaudRatePrescaler = _ps_table_[ps_idx].divisor_macro;

    // polarity setting
    switch(settings->polarity) {
    case LEADING_RISING_EDGE:
        handler->Init.CLKPhase = SPI_PHASE_1EDGE;
        handler->Init.CLKPolarity = SPI_POLARITY_LOW;
        break;
    case LEADING_FALLING_EDGE:
        handler->Init.CLKPhase = SPI_PHASE_1EDGE;
        handler->Init.CLKPolarity = SPI_POLARITY_HIGH;
        break;
    case TRAILING_RISING_EDGE:
        handler->Init.CLKPhase = SPI_PHASE_2EDGE;
        handler->Init.CLKPolarity = SPI_POLARITY_HIGH;
        break;
    case TRAILING_FALLING_EDGE:
        handler->Init.CLKPhase = SPI_PHASE_2EDGE;
        handler->Init.CLKPolarity = SPI_POLARITY_LOW;
        break;
    default:
        KB_DEBUG_ERROR("Wrong Polarity selected!.\r\n");
        return KB_ERROR;
    }

    int8_t status = HAL_SPI_Init(handler);
    KB_CONVERT_STATUS(status);
    if (status != KB_OK) {
        KB_DEBUG_ERROR("Error initializing.\r\n");
    }
    return	status;
}


int kb_spi_mosi_pin(kb_spi_t spi, kb_gpio_pin_t pin, kb_gpio_pull_t pull)
{
    uint32_t alternate = GPIO_SPI_MOSI_AF_(spi, pin);
    if (alternate == KB_WRONG_PIN) {
        KB_DEBUG_ERROR("Wrong MOSI pin! Find a correct one.\r\n");
        return KB_ERROR;
    }
    kb_gpio_enable_clk(port);
    // Init GPIOs
    kb_gpio_init_t gpio_setting = {
        .Mode = GPIO_MODE_AF_PP,
        .Pull = pull,
        .Alternate = alternate,
        .Speed = GPIO_SPEED_FREQ_VERY_HIGH // 50MHz
    };
    kb_gpio_init(pin, &gpio_setting);
    return KB_OK;
}


int kb_spi_miso_pin(kb_spi_t spi, kb_gpio_pin_t pin, kb_gpio_pull_t pull)
{
    uint32_t alternate = GPIO_SPI_MISO_AF_(spi, port, pin);
    if (alternate == KB_WRONG_PIN) {
        KB_DEBUG_ERROR("Wrong MISO pin! Find a correct one.\r\n");
        return KB_ERROR;
    }
    kb_gpio_enable_clk(port);
    // Init GPIOs
    kb_gpio_init_t gpio_setting = {
        .Mode = GPIO_MODE_AF_PP,
        .Pull = pull,
        .Alternate = alternate,
        .Speed = GPIO_SPEED_FREQ_VERY_HIGH // 50MHz
    };
    kb_gpio_init(pin, &gpio_setting);
    return KB_OK;
}


int kb_spi_sck_pin(kb_spi_t spi, kb_gpio_pin_t pin, kb_gpio_pull_t pull)
{
    uint32_t alternate = GPIO_SPI_SCK_AF_(spi, port, pin);
    if (alternate == KB_WRONG_PIN) {
        KB_DEBUG_ERROR("Wrong SCK pin! Find a correct one.\r\n");
        return KB_ERROR;
    }
    kb_gpio_enable_clk(port);
    // Init GPIOs
    kb_gpio_init_t gpio_setting = {
        .Mode = GPIO_MODE_AF_PP,
        .Pull = pull,
        .Alternate = alternate,
        .Speed = GPIO_SPEED_FREQ_VERY_HIGH // 50MHz
    };
    kb_gpio_init(pin, &gpio_setting);
    return KB_OK;
}


inline int kb_spi_send(kb_spi_t spi, uint8_t* buf, uint16_t size)
{
    return kb_spi_send_timeout(spi, buf, size, TIMEOUT_MAX);
}


int kb_spi_send_timeout(kb_spi_t spi, uint8_t *buf, uint16_t size, uint32_t timeout)
{
    // select handler
    SPI_HandleTypeDef* handler = _get_handler(spi);
    if (NULL == handler) {
        return KB_ERROR;
    }

    int8_t status = HAL_SPI_Transmit(handler, buf, size, timeout);
    KB_CONVERT_STATUS(status);
    if (status != KB_OK) {
        KB_DEBUG_ERROR("Error in sending.\r\n");
    }
    return status;
}


int kb_spi_receive(kb_spi_t spi, uint8_t* buf, uint16_t size)
{
    return kb_spi_receive_timeout(spi, buf, size, TIMEOUT_MAX);
}


int kb_spi_receive_timeout(kb_spi_t spi, uint8_t *buf, uint16_t size, uint32_t timeout)
{
    // select handler
    SPI_HandleTypeDef* handler = _get_handler(spi);
    if (NULL == handler) {
        return KB_ERROR;
    }

    int8_t status = HAL_SPI_Receive(handler, buf, size, timeout);
    KB_CONVERT_STATUS(status);
    if (status != KB_OK) {
        KB_DEBUG_ERROR("Error in receiving.\r\n");
    }
    return status;
}


inline int kb_spi_sendreceive(kb_spi_t spi, uint8_t *tx_buf, uint8_t *rx_buf, uint16_t size)
{
    return kb_spi_sendreceive_timeout(spi, tx_buf, rx_buf, size, TIMEOUT_MAX);
}


int kb_spi_sendreceive_timeout(kb_spi_t spi, uint8_t *tx_buf, uint8_t *rx_buf, uint16_t size, uint32_t timeout)
{
    // select handler
    SPI_HandleTypeDef* handler = _get_handler(spi);
    if (NULL == handler) {
        return KB_ERROR;
    }

    int8_t status = HAL_SPI_TransmitReceive(handler, tx_buf, rx_buf, size, timeout);
    KB_CONVERT_STATUS(status);
    if (status != KB_OK) {
        KB_DEBUG_ERROR("Error in sending/receiving.\r\n");
    }
    return status;
}

/******************************************************************************
 * Private Functions
 ******************************************************************************/

static uint32_t _get_bus_freq(kb_spi_t spi)
{
    if ((spi == SPI_2) || (spi == SPI_3)) {	// APB1: SPI2, SPI3
        return HAL_RCC_GetPCLK1Freq();
    } else if ((spi == SPI_1) || (spi == SPI_4)) {	// APB2: SPI1, SPI4
        return HAL_RCC_GetPCLK2Freq();
    }
    KB_DEBUG_ERROR("Wrong SPI device! Find a correct one.\r\n");
    return 0;
}


static SPI_HandleTypeDef * _get_handler (kb_spi_t spi)
{
#if defined(STM32F446xx)
    static SPI_HandleTypeDef _spi_handler_table[] = {
        {.Instance = SPI1}, {.Instance = SPI2}, {.Instance = SPI3}, {.Instance = SPI4}
    };
#else
    #error "Please define device! " __FILE__ "\n"
#endif
    return &_spi_handler_table[(int)spi];
}


static void _enable_spi_clk (kb_spi_t spi)
{
    if (spi == SPI1) {
        __SPI1_CLK_ENABLE();
    } else if (spi == SPI2) {
        __SPI2_CLK_ENABLE();
    } else if (spi == SPI3) {
        __SPI3_CLK_ENABLE();
    } else if (spi == SPI4) {
        __SPI4_CLK_ENABLE();
    } else {
        KB_DEBUG_ERROR("Wrong SPI device selected!\r\n");
    }
    return;
}


#if defined(STM32F446xx)
    static const uint8_t _ps_table_size = 8;
    static const struct _prescaler _ps_table[] = {
        {2, SPI_BAUDRATEPRESCALER_2},
        {4, SPI_BAUDRATEPRESCALER_4},
        {8, SPI_BAUDRATEPRESCALER_8},
        {16, SPI_BAUDRATEPRESCALER_16},
        {32, SPI_BAUDRATEPRESCALER_32},
        {64, SPI_BAUDRATEPRESCALER_64},
        {128, SPI_BAUDRATEPRESCALER_128},
        {256, SPI_BAUDRATEPRESCALER_256}
    };
#else
    #error "Please define device!"
#endif
