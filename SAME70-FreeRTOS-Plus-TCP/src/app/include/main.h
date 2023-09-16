/*****************************************************************************\
 * main.h: Includes and declarations for the application scope                *
 *  Author: Peter Herrmann                                                   *
\*****************************************************************************/

#ifndef MAIN_H_
#define MAIN_H_

/* FreeRTOS Kernel */
#include <FreeRTOS.h>
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
#include "FreeRTOS_ARP.h"
#include "FreeRTOS_DHCP.h"
#include "FreeRTOS_IP.h"
#include "FreeRTOS_Sockets.h"
#include "NetworkBufferManagement.h"
#include "NetworkInterface.h"
#include "gmac_SAM.h"
#if (ipconfigUSE_IPv6 != 0)
#include "FreeRTOS_ND.h"
#endif
#if (USE_LOG_EVENT != 0)
#include "eventLogging.h"
#endif
#if (ipconfigMULTI_INTERFACE != 0)
#include "FreeRTOS_Routing.h"
#endif
/* Standard Library */
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
/* ASF */
#include "asf.h"
#include "conf_board.h"
#include "conf_clock.h"
#include "stdio_serial.h"

#define mainHOST_NAME BOARD_NAME

void vSeedRand(UBaseType_t ulSeed);

/* FreeRTOS Kernel Hooks */
extern void vApplicationStackOverflowHook(xTaskHandle *pxTask,
                                          signed char *pcTaskName);
extern void vApplicationIdleHook(void);
extern void vApplicationTickHook(void);
extern void vApplicationMallocFailedHook(void);
extern void xPortSysTickHandler(void);

/* FreeRTOS+TCP Library Hooks */
extern BaseType_t xApplicationGetRandomNumber(uint32_t *pulNumber);
extern uint32_t ulApplicationGetNextSequenceNumber(
    uint32_t ulSourceAddress, uint16_t usSourcePort,
    uint32_t ulDestinationAddress, uint16_t usDestinationPort);
extern BaseType_t xApplicationDNSQueryHook(const char *pcName);
extern BaseType_t xApplicationDNSQueryHook_Multi(
    struct xNetworkEndPoint *pxEndPoint, const char *pcName);
extern void vApplicationIPNetworkEventHook_Multi(
    eIPCallbackEvent_t eNetworkEvent, struct xNetworkEndPoint *pxEndPoint);
extern NetworkInterface_t *pxSAM_FillInterfaceDescriptor(
    BaseType_t xEMACIndex, NetworkInterface_t *pxInterface);

#endif /* MAIN_H_ */