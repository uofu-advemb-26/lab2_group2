#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "pico/stdlib.h"

#define MAIN_TASK_PRIORITY   ( tskIDLE_PRIORITY + 1UL )
#define MAIN_TASK_STACK_SIZE configMINIMAL_STACK_SIZE

char switch_case(char c);
void main_task(__unused void *params);
void create_console_task(void);

#endif
