/*****************************************************************************\
 * main.c: A very minimal implementation of FreeRTOS+TCP on a SAME70         *
 *         microconroller. The program will blink an LED regularly, request  *
 *         DHCP least, respond to ICMP pings, and broadcast ARP .
 *  Author: Peter Herrmann                                                   *
\*****************************************************************************/

#include "main.h"
#include "LED_task.h"


/* Default ipconfig. If DHCP is enabled, this will be overwritten. */
static const uint8_t ucIPAddress[ 4 ] = {configIP_ADDR0, 
                                         configIP_ADDR1, 
                                         configIP_ADDR2, 
                                         configIP_ADDR3 };

static const uint8_t ucNetMask[ 4 ] = { configNET_MASK0, 
                                        configNET_MASK1, 
                                        configNET_MASK2, 
                                        configNET_MASK3 };

static const uint8_t ucGatewayAddress[ 4 ] = { configGATEWAY_ADDR0, 
                                               configGATEWAY_ADDR1, 
                                               configGATEWAY_ADDR2, 
                                               configGATEWAY_ADDR3 };

static const uint8_t ucDNSServerAddress[ 4 ] = { configDNS_SERVER_ADDR0, 
                                                 configDNS_SERVER_ADDR1, 
                                                 configDNS_SERVER_ADDR2, 
                                                 configDNS_SERVER_ADDR3 };

const uint8_t ucMACAddress[ 6 ] = { configMAC_ADDR0, 
                                    configMAC_ADDR1, 
                                    configMAC_ADDR2, 
                                    configMAC_ADDR3, 
                                    configMAC_ADDR4, 
                                    configMAC_ADDR5 };


int main(void)
{
    sysclk_init();
    board_init();
    configure_console();

    pmc_enable_periph_clk(ID_GMAC);
    pmc_enable_periph_clk(ID_PIOA);
    pmc_enable_periph_clk(ID_PIOB);
    vEthernetInit();
    vSeedRand( ( uint32_t ) main );

    FreeRTOS_IPInit(ucIPAddress, 
                    ucNetMask, 
                    ucGatewayAddress, 
                    ucDNSServerAddress, 
                    ucMACAddress );

    printf("\n\r-- FreeRTOS+TCP Example on %s --\n\r", BOARD_NAME);
    printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);

    if (xTaskCreate(LED_task, 
                    "LED", 
                    TASK_LED_STACK_SIZE, 
                    NULL,
                    TASK_LED_STACK_PRIORITY, 
                    NULL) != pdPASS) 
    {
        printf("Failed to create test led task\r\n");
    }

    vTaskStartScheduler();

    return 0;
}


static void configure_console(void)
{
    const usart_serial_options_t uart_serial_options = {
        .baudrate = CONF_UART_BAUDRATE,
    #if (defined CONF_UART_CHAR_LENGTH)
        .charlength = CONF_UART_CHAR_LENGTH,
    #endif
        .paritytype = CONF_UART_PARITY,
    #if (defined CONF_UART_STOP_BITS)
        .stopbits = CONF_UART_STOP_BITS,
    #endif
    };

    /* Configure console UART. */
    stdio_serial_init(CONF_UART, &uart_serial_options);

    /* Specify that stdout should not be buffered. */
    #if defined(__GNUC__)
        setbuf(stdout, NULL);
    #endif
}


static void vEthernetInit()
{
    pio_set_output(PIN_GMAC_RESET_PIO, PIN_GMAC_RESET_MASK, 1,  false, true);
    pio_set_input(PIN_GMAC_INT_PIO, PIN_GMAC_INT_MASK, PIO_PULLUP);
    pio_set_peripheral(PIN_GMAC_PIO, PIN_GMAC_PERIPH, PIN_GMAC_MASK);

    /* Configure GMAC runtime clock */
    gmac_set_mdc_clock(GMAC, sysclk_get_cpu_hz());
    sysclk_get_cpu_hz();
}
