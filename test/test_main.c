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
    hard_assert(cyw43_arch_init() == PICO_OK);
    while (1) {
        sleep_ms(5000); // Give time for TTY to attach.
        printf("Start tests\n");
        UNITY_BEGIN();

        // Run console.c tests
        RUN_TEST(test_console_toUppercase);
        RUN_TEST(test_console_toLowercase);
        RUN_TEST(test_console_notAlpha);

        // Run blink.c tests
        RUN_TEST(test_led_off);
        RUN_TEST(test_led_on);

        UNITY_END();
        sleep_ms(5000);
    }
}
