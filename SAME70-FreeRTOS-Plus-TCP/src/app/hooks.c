/*****************************************************************************\
 * hooks.c: Definitions of the applicaiton hooks provided by a FreeRTOS      *
 *          application.                                                     *
 *  Author: Peter Herrmann                                                   *
\*****************************************************************************/

#include "main.h"

///////////////////////////////
//// FreeRTOS Kernel Hooks ////
///////////////////////////////

extern void vApplicationStackOverflowHook(xTaskHandle *pxTask, signed char *pcTaskName)
{
	for (;;) { }
}


extern void vApplicationMallocFailedHook(void)
{
	for (;;) { }
}


extern void vApplicationIdleHook(void) { /*  */ }
extern void vApplicationTickHook(void) { /*  */ }


///////////////////////////////
//// Random Number Utility ////
///////////////////////////////

static UBaseType_t ulNextRand;

/* Generate psuedo-random number. Must be seeded first with vSeedRand(). */
UBaseType_t uxRand( void )
{
    const uint32_t ulMultiplier = 0x015a4e35UL, ulIncrement = 1UL;

    ulNextRand = ( ulMultiplier * ulNextRand ) + ulIncrement;
    return( ( int ) ( ulNextRand >> 16UL ) & 0x7fffUL );
}


/* Set the seed for use with uxRand() */
void vSeedRand( UBaseType_t ulSeed )
{
    ulNextRand = ulSeed;
}


//////////////////////////////
//// FreeRTOS + TCP Hooks ////
//////////////////////////////


uint32_t ulApplicationGetNextSequenceNumber( uint32_t ulSourceAddress,
                                             uint16_t usSourcePort,
                                             uint32_t ulDestinationAddress,
                                             uint16_t usDestinationPort )
{
    return uxRand();
}


BaseType_t xApplicationGetRandomNumber( uint32_t * pulNumber )
{
    return (BaseType_t) uxRand();
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
        
        if( xTasksAlreadyCreated == pdFALSE )
        {
            /* Create tasks dependent on NetworkUp here */
            xTasksAlreadyCreated = pdTRUE;
        }

        /* Print ipconfig to console */
        FreeRTOS_GetAddressConfiguration( &ulIPAddress, &ulNetMask, &ulGatewayAddress, &ulDNSServerAddress );
        FreeRTOS_inet_ntoa( ulIPAddress, cBuffer );
        printf("\r\n\nIP Address:         ");
        printf("%s", cBuffer);

        FreeRTOS_inet_ntoa( ulNetMask, cBuffer );
        printf("\r\nSubnet Mask:        ");
        printf("%s", cBuffer);

        FreeRTOS_inet_ntoa( ulGatewayAddress, cBuffer );
        printf("\r\nGateway Address:    ");
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
