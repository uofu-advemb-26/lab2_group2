/**
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"

#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/cyw43_arch.h"

#include "blink.h"
#include "console.h"

#define MAIN_TASK_PRIORITY      ( tskIDLE_PRIORITY + 1UL )

#define MAIN_TASK_STACK_SIZE configMINIMAL_STACK_SIZE

void main_task(__unused void *params) {
    // Copy any input characters to output and flip their case (lowercase -> uppercase; uppercase -> lowercase)
    char c;
    while(c = getchar()) {
        if (c <= 'z' && c >= 'a') putchar(c - 32); // Switch to uppercase
        else if (c >= 'A' && c <= 'Z') putchar(c + 32); // Switch to lowercase
        else putchar(c); // No flips on non-alphabetical characters
    }
}

int main( void )
{
    // Initialize the standard IO ports for UART communication
    stdio_init_all();
    
    // Name of RTOS appears to be unused
    const char *rtos_name;
    rtos_name = "FreeRTOS";

    // Create the console task with a minimal stack and low priority; pass no parameters
    TaskHandle_t task;
    xTaskCreate(main_task, "MainThread",
                MAIN_TASK_STACK_SIZE, NULL, MAIN_TASK_PRIORITY, &task);

    create_blink_task();

    // Enter the FreeRTOS scheduler (no return)
    vTaskStartScheduler();
    return 0;
}
