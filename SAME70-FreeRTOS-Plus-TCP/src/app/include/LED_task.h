/*****************************************************************************\
 * LED_task.h: FreeRTOS Task for blinky LED                                  *
 *  Author: Peter Herrmann                                                   *
\*****************************************************************************/

#ifndef LED_TASK_H_
#define LED_TASK_H_

#include "main.h"

#define TASK_LED_STACK_SIZE         (1024/sizeof(portSTACK_TYPE))
#define TASK_LED_STACK_PRIORITY     (tskIDLE_PRIORITY)

void LED_task(void *pvParameters);


#endif /* LED_TASK_H_ */