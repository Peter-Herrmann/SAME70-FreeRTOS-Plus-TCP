/*****************************************************************************\
 * main.c: A very minimal implementation of FreeRTOS+TCP on a SAME70         *
 *         microconroller. The program will blink an LED regularly, request  *
 *         and renew a DHCP lease, respond to ICMP pings, manage ARP.        *
 *  Author: Peter Herrmann                                                   *
\*****************************************************************************/

#include "main.h"
#include "LED_task.h"

static void vEthernetInit(void);
static void vNetworkInterfaceInit(void);
static void configure_console(void);

BaseType_t xEndPointCount = 0;
static NetworkInterface_t xInterfaces[1];
static NetworkEndPoint_t xEndPoints[4];

/* Default ipconfig. If DHCP is enabled, these will be overwritten. */
static const uint8_t ucIPAddress[4] = {configIP_ADDR0, configIP_ADDR1,
                                       configIP_ADDR2, configIP_ADDR3};

static const uint8_t ucNetMask[4] = {configNET_MASK0, configNET_MASK1,
                                     configNET_MASK2, configNET_MASK3};

static const uint8_t ucGatewayAddress[4] = {
    configGATEWAY_ADDR0, configGATEWAY_ADDR1, configGATEWAY_ADDR2,
    configGATEWAY_ADDR3};

static const uint8_t ucDNSServerAddress[4] = {
    configDNS_SERVER_ADDR0, configDNS_SERVER_ADDR1, configDNS_SERVER_ADDR2,
    configDNS_SERVER_ADDR3};

const uint8_t ucMACAddress[6] = {configMAC_ADDR0, configMAC_ADDR1,
                                 configMAC_ADDR2, configMAC_ADDR3,
                                 configMAC_ADDR4, configMAC_ADDR5};

int main(void)
{
    sysclk_init();
    board_init();
    configure_console();

    pmc_enable_periph_clk(ID_GMAC);
    pmc_enable_periph_clk(ID_PIOA);
    pmc_enable_periph_clk(ID_PIOB);
    vEthernetInit();
    vSeedRand((uint32_t)main);
    vNetworkInterfaceInit();

    printf("\n\r-- FreeRTOS+TCP Example on %s --\n\r", BOARD_NAME);
    printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);

    if (xTaskCreate(LED_task, "LED", TASK_LED_STACK_SIZE, NULL,
                    TASK_LED_STACK_PRIORITY, NULL) != pdPASS)
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
    pio_set_output(PIN_GMAC_RESET_PIO, PIN_GMAC_RESET_MASK, 1, false, true);
    pio_set_input(PIN_GMAC_INT_PIO, PIN_GMAC_INT_MASK, PIO_PULLUP);
    pio_set_peripheral(PIN_GMAC_PIO, PIN_GMAC_PERIPH, PIN_GMAC_MASK);

    /* Configure GMAC runtime clock */
    gmac_set_mdc_clock(GMAC, sysclk_get_cpu_hz());
    sysclk_get_cpu_hz();
}

static void vNetworkInterfaceInit(void)
{
    pxSAM_FillInterfaceDescriptor(0, &(xInterfaces[0]));
    pxNetworkInterfaces = &(xInterfaces[0]);
#if (ipconfigUSE_IPv4 != 0)
    {
        FreeRTOS_FillEndPoint(&(xInterfaces[0]), &(xEndPoints[xEndPointCount]),
                              ucIPAddress, ucNetMask, ucGatewayAddress,
                              ucDNSServerAddress, ucMACAddress);
#if (ipconfigUSE_DHCP != 0)
        {
            /* End-point 0 wants to use DHCPv4. */
            xEndPoints[xEndPointCount].bits.bWantDHCP = pdTRUE;

#endif /* ( ipconfigUSE_DHCP != 0 ) */

            xEndPointCount += 1;
        }
    }
#endif /* ( ipconfigUSE_IPv4 != 0 */

#if (ipconfigUSE_IPv6 != 0)
    /*
     *     End-point-1 : public
     *     Network: 2001:470:ed44::/64
     *     IPv6   : 2001:470:ed44::4514:89d5:4589:8b79/128
     *     Gateway: fe80::ba27:ebff:fe5a:d751  // obtained from Router
     * Advertisement
     */
    {
        IPv6_Address_t xIPAddress;
        IPv6_Address_t xPrefix;
        IPv6_Address_t xGateWay;
        IPv6_Address_t xDNSServer1, xDNSServer2;

        FreeRTOS_inet_pton6("2001:470:ed44::", xPrefix.ucBytes);

        FreeRTOS_CreateIPv6Address(&xIPAddress, &xPrefix, 64, pdTRUE);
        FreeRTOS_inet_pton6("fe80::ba27:ebff:fe5a:d751", xGateWay.ucBytes);

        FreeRTOS_FillEndPoint_IPv6(
            &(xInterfaces[0]), &(xEndPoints[xEndPointCount]), &(xIPAddress),
            &(xPrefix), 64uL,  /* Prefix length. */
            &(xGateWay), NULL, /* pxDNSServerAddress: Not used yet. */
            ucMACAddress);
        FreeRTOS_inet_pton6("2001:4860:4860::8888",
                            xEndPoints[xEndPointCount]
                                .ipv6_settings.xDNSServerAddresses[0]
                                .ucBytes);
        FreeRTOS_inet_pton6("fe80::1", xEndPoints[xEndPointCount]
                                           .ipv6_settings.xDNSServerAddresses[1]
                                           .ucBytes);
        FreeRTOS_inet_pton6("2001:4860:4860::8888",
                            xEndPoints[xEndPointCount]
                                .ipv6_defaults.xDNSServerAddresses[0]
                                .ucBytes);
        FreeRTOS_inet_pton6("fe80::1", xEndPoints[xEndPointCount]
                                           .ipv6_defaults.xDNSServerAddresses[1]
                                           .ucBytes);

#if (ipconfigUSE_RA != 0)
        {
            /* End-point 1 wants to use Router Advertisement */
            xEndPoints[xEndPointCount].bits.bWantRA = pdTRUE;
        }
#endif /* #if( ipconfigUSE_RA != 0 ) */

#if (ipconfigUSE_DHCPv6 != 0)
        {
            /* End-point 1 wants to use DHCPv6. */
            xEndPoints[xEndPointCount].bits.bWantDHCP = pdTRUE;
        }
#endif /* ( ipconfigUSE_DHCPv6 != 0 ) */

        xEndPointCount += 1;
    }

    /*
     *     End-point-3 : private
     *     Network: fe80::/10 (link-local)
     *     IPv6   : fe80::7009
     *     Gateway: -
     */
    {
        IPv6_Address_t xIPAddress;
        IPv6_Address_t xPrefix;

        FreeRTOS_inet_pton6("fe80::", xPrefix.ucBytes);
        FreeRTOS_inet_pton6("fe80::7009", xIPAddress.ucBytes);

        FreeRTOS_FillEndPoint_IPv6(&(xInterfaces[0]),
                                   &(xEndPoints[xEndPointCount]), &(xIPAddress),
                                   &(xPrefix), 10U, /* Prefix length. */
                                   NULL,            /* No gateway */
                                   NULL, /* pxDNSServerAddress: Not used yet. */
                                   ucMACAddress);

        xEndPointCount += 1;
    }

#endif /* ( ipconfigUSE_IPv6 != 0 ) */

    /* Initialise the TCP/IP stack. */
    FreeRTOS_IPInit_Multi();
}