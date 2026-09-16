/**
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "FreeRTOS.h"
#include "blink.h"
#include "console.h"

int main( void )
{
    // Initialize the standard IO ports for UART communication
    stdio_init_all();
    
    // Name of RTOS appears to be unused
    const char *rtos_name;
    rtos_name = "FreeRTOS";

    // Create the two tasks required for this program
    create_console_task();
    create_blink_task();

    // Enter the FreeRTOS scheduler (no return)
    vTaskStartScheduler();
    return 0;
}
