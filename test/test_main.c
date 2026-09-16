#include <stdio.h>
#include <pico/stdlib.h>
#include <stdint.h>
#include <unity.h>
#include "unity_config.h"
#include "test_blink.h"
#include "test_console.h"

void setUp(void) {}

void tearDown(void) {}

int main (void)
{
    stdio_init_all();
    while (1) {
        sleep_ms(5000); // Give time for TTY to attach.
        printf("Start tests\n");
        UNITY_BEGIN();
        // RUN_TEST(function);
        sleep_ms(5000);
        UNITY_END();
    }
}
