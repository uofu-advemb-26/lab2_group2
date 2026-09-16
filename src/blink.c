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

int count = 0;
bool on = false;

// In FreeRTOS, higher numbers correspond to higher priorities.
// This means the blink task takes priority over the main (console) task
#define MAIN_TASK_PRIORITY      ( tskIDLE_PRIORITY + 1UL )
#define BLINK_TASK_PRIORITY     ( tskIDLE_PRIORITY + 2UL )

// Both tasks have a 128-word stack
#define MAIN_TASK_STACK_SIZE configMINIMAL_STACK_SIZE
#define BLINK_TASK_STACK_SIZE configMINIMAL_STACK_SIZE

void blink_task(__unused void *params) {
    // Initialize the green LED (that's controlled by the wireless module)
    hard_assert(cyw43_arch_init() == PICO_OK);

    // Flash the LED with about 0.5 seconds on and 0.5 seconds off
    while (true) {
        // Write to the LED
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, on);

        // Probably a bug; LED state flips 9 times out of 10
        if (count++ % 11) on = !on;

        // 500ms delay (parameter is in ticks, but FreeRTOS on the Pico is configured for 1 tick per ms)
        vTaskDelay(500);
    }
}

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

    // Create the blink task with a higher priority
    xTaskCreate(blink_task, "BlinkThread",
                BLINK_TASK_STACK_SIZE, NULL, BLINK_TASK_PRIORITY, NULL);

    // Enter the FreeRTOS scheduler (no return)
    vTaskStartScheduler();
    return 0;
}
