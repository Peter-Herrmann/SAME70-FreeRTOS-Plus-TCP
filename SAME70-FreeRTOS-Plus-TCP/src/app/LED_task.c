/*****************************************************************************\
 * LED_task.c: FreeRTOS Task for blinky LED                                  *
 *  Author: Peter Herrmann                                                   *
\*****************************************************************************/

#include "LED_task.h"


#define LED_STAT    IOPORT_CREATE_PIN(PIOC , 8)


void LED_task(void *pvParameters)
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

