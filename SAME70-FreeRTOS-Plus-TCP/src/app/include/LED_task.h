/*
 * LED_task.h
 *
 * Created: 8/30/2023 12:03:00 PM
 *  Author: pherrman
 */ 


#ifndef LED_TASK_H_
#define LED_TASK_H_

#include "main.h"

#define TASK_LED_STACK_SIZE         (1024/sizeof(portSTACK_TYPE))
#define TASK_LED_STACK_PRIORITY     (tskIDLE_PRIORITY)

void LED_task(void *pvParameters);


#endif /* LED_TASK_H_ */