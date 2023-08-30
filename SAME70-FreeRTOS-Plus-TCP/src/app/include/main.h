/*****************************************************************************\
 * main.h: Includes and declarations for he application scope                *
 *  Author: Peter Herrmann                                                   *
\*****************************************************************************/


#ifndef MAIN_H_
#define MAIN_H_


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

#define mainHOST_NAME               "SAME70"


void vSeedRand( UBaseType_t ulSeed );
static void vEthernetInit( void );
static void configure_console(void);

extern void vApplicationStackOverflowHook(xTaskHandle *pxTask, signed char *pcTaskName);
extern void vApplicationIdleHook(void);
extern void vApplicationTickHook(void);
extern void vApplicationMallocFailedHook(void);
extern void xPortSysTickHandler(void);


#endif /* MAIN_H_ */