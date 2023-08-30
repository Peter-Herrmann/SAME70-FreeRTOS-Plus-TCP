/*
 * hooks.c
 *
 * Created: 8/30/2023 12:08:43 PM
 *  Author: pherrman
 */ 

#include "main.h"

static UBaseType_t ulNextRand;

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


//////////////////////////////
//// FreeRTOS + TCP Hooks ////
//////////////////////////////

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
            xTasksAlreadyCreated = pdTRUE;
        }

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