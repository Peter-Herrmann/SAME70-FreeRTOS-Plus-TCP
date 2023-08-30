

/* FreeRTOS Kernel */
#include <FreeRTOS.h>
#include <stack_macros.h>
#include <croutine.h>
#include <deprecated_definitions.h>
#include <event_groups.h>
#include <list.h>
#include <message_buffer.h>
#include <mpu_wrappers.h>
#include <portable.h>
#include <projdefs.h>
#include <queue.h>
#include <semphr.h>
#include <stack_macros.h>
#include <stream_buffer.h>
#include <task.h>
#include <timers.h>
/* FreeRTOS Plus TCP */
#include "FreeRTOS_IP.h"
#include "FreeRTOS_Sockets.h"
#include "FreeRTOS_DHCP.h"
#include "NetworkBufferManagement.h"
#include "FreeRTOS_ARP.h"
#include "NetworkInterface.h"
#include "gmac_SAM.h"
#if( ipconfigUSE_IPv6 != 0 )
    #include "FreeRTOS_ND.h"
#endif
#if( USE_LOG_EVENT != 0 )
    #include "eventLogging.h"
#endif
#if( ipconfigMULTI_INTERFACE != 0 )
    #include "FreeRTOS_Routing.h"
#endif
/* Standard Library */
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
/* ASF */
#include "asf.h"
#include "stdio_serial.h"
#include "conf_board.h"
#include "conf_clock.h"



#define mainHOST_NAME               "SAME70Q21"
#define TASK_LED_STACK_SIZE         (1024/sizeof(portSTACK_TYPE))
#define TASK_LED_STACK_PRIORITY     (tskIDLE_PRIORITY)



extern void vApplicationStackOverflowHook(xTaskHandle *pxTask, signed char *pcTaskName);
extern void vApplicationIdleHook(void);
extern void vApplicationTickHook(void);
extern void vApplicationMallocFailedHook(void);
extern void xPortSysTickHandler(void);



static UBaseType_t ulNextRand;
U8 rxbuf[512];
static const uint8_t ucIPAddress[ 4 ] = { configIP_ADDR0, configIP_ADDR1, configIP_ADDR2, configIP_ADDR3 };
static const uint8_t ucNetMask[ 4 ] = { configNET_MASK0, configNET_MASK1, configNET_MASK2, configNET_MASK3 };
static const uint8_t ucGatewayAddress[ 4 ] = { configGATEWAY_ADDR0, configGATEWAY_ADDR1, configGATEWAY_ADDR2, configGATEWAY_ADDR3 };
static const uint8_t ucDNSServerAddress[ 4 ] = { configDNS_SERVER_ADDR0, configDNS_SERVER_ADDR1, configDNS_SERVER_ADDR2, configDNS_SERVER_ADDR3 };
const uint8_t ucMACAddress[ 6 ] = { configMAC_ADDR0, configMAC_ADDR1, configMAC_ADDR2, configMAC_ADDR3, configMAC_ADDR4, configMAC_ADDR5 };



static void prvSRand( UBaseType_t ulSeed );
static void vEthernetInit( void );
static void configure_console(void);
static void task_led(void *pvParameters);



int main(void)
{
    sysclk_init();
    board_init();
    configure_console();

    pmc_enable_periph_clk(ID_GMAC);
    pmc_enable_periph_clk(ID_PIOA);
    pmc_enable_periph_clk(ID_PIOB);

    vEthernetInit();
    prvSRand( ( uint32_t ) main );
    FreeRTOS_IPInit(ucIPAddress, 
                    ucNetMask, 
                    ucGatewayAddress, 
                    ucDNSServerAddress, 
                    ucMACAddress );

    printf("-- Freertos Example --\n\r");
    printf("-- %s\n\r", BOARD_NAME);
    printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);

    if (xTaskCreate(task_led, 
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



extern void vApplicationStackOverflowHook(xTaskHandle *pxTask, signed char *pcTaskName)
{
    printf("stack overflow %x %s\r\n", pxTask, (portCHAR *)pcTaskName);
    for (;;) { }
}



extern void vApplicationMallocFailedHook(void)
{
    for (;;) { }
}



extern void vApplicationIdleHook(void) { /*  */ }
extern void vApplicationTickHook(void) { /*  */ }



#define LED_STAT    IOPORT_CREATE_PIN(PIOC , 8)
static void task_led(void *pvParameters)
{
    UNUSED(pvParameters);
    ioport_set_pin_dir(LED_STAT, IOPORT_DIR_OUTPUT);
    for (;;) 
	{
        ioport_toggle_pin_level(LED_STAT);
		//printf(" .");
        vTaskDelay(100);
    }
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



UBaseType_t uxRand( void )
{
    const uint32_t ulMultiplier = 0x015a4e35UL, ulIncrement = 1UL;

    /* Utility function to generate a pseudo random number. */

    ulNextRand = ( ulMultiplier * ulNextRand ) + ulIncrement;
    return( ( int ) ( ulNextRand >> 16UL ) & 0x7fffUL );
}



static void prvSRand( UBaseType_t ulSeed )
{
    /* Utility function to seed the pseudo random number generator. */
    ulNextRand = ulSeed;
}



uint32_t ulApplicationGetNextSequenceNumber( uint32_t ulSourceAddress,
                                             uint16_t usSourcePort,
                                             uint32_t ulDestinationAddress,
                                             uint16_t usDestinationPort )
{
    return uxRand();
}



void vApplicationIPNetworkEventHook( eIPCallbackEvent_t eNetworkEvent )
{
    uint32_t ulIPAddress, ulNetMask, ulGatewayAddress, ulDNSServerAddress;
    char cBuffer[ 16 ];
    static BaseType_t xTasksAlreadyCreated = pdFALSE;

    FreeRTOS_printf( ( "vApplicationIPNetworkEventHook: event %ld\n", eNetworkEvent ) );

    /* If the network has just come up...*/
    if( eNetworkEvent == eNetworkUp )
    {
        /* Create the tasks that use the IP stack if they have not already been
        created. */
        if( xTasksAlreadyCreated == pdFALSE )
        {
            #if( mainCREATE_TCP_ECHO_CLIENT_TASKS_SINGLE == 1 )
            {
                vStartTCPEchoClientTasks_SingleTasks( mainECHO_CLIENT_TASK_STACK_SIZE, mainECHO_CLIENT_TASK_PRIORITY );
            }
            #endif

            #if( mainCREATE_SIMPLE_TCP_ECHO_SERVER == 1 )
            {
                vStartSimpleTCPServerTasks( mainECHO_SERVER_STACK_SIZE, mainECHO_SERVER_TASK_PRIORITY );
            }
            #endif

            xTasksAlreadyCreated = pdTRUE;
        }

        /* Print out the network configuration, which may have come from a DHCP
        server. */
        FreeRTOS_GetAddressConfiguration( &ulIPAddress, &ulNetMask, &ulGatewayAddress, &ulDNSServerAddress );
        FreeRTOS_inet_ntoa( ulIPAddress, cBuffer );
        printf("\r\nIP Address: ");
        printf("%s", cBuffer);

        FreeRTOS_inet_ntoa( ulNetMask, cBuffer );
        printf("\r\nSubnet Mask: ");
        printf("%s", cBuffer);

        FreeRTOS_inet_ntoa( ulGatewayAddress, cBuffer );
        printf("\r\nGateway Address: ");
        printf("%s", cBuffer);

        FreeRTOS_inet_ntoa( ulDNSServerAddress, cBuffer );
        printf("\r\nDNS Server Address: ");
        printf("%s", cBuffer);
    }
}



BaseType_t xApplicationDNSQueryHook( const char *pcName )
{
    return strcmp(pcName, pcApplicationHostnameHook()) ? pdFAIL : pdPASS;
}



const char *pcApplicationHostnameHook( void )
{
    return mainHOST_NAME;
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
