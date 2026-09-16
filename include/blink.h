#ifndef _BLINK_H_
#define _BLINK_H_

#include "FreeRTOS.h"
#include "task.h"

#include "pico/cyw43_arch.h"

#define BLINK_TASK_PRIORITY   ( tskIDLE_PRIORITY + 2UL )
#define BLINK_TASK_STACK_SIZE configMINIMAL_STACK_SIZE

void create_blink_task(void);
void blink_task(__unused void *params);

#endif