#include "test_blink.h"

void test_led_off() {
    write_led(0);
    TEST_ASSERT_FALSE_MESSAGE(cyw43_arch_gpio_get(CYW43_WL_GPIO_LED_PIN), "Failed to turn LED off");
}

void test_led_on() {
    write_led(1);
    TEST_ASSERT_TRUE_MESSAGE(cyw43_arch_gpio_get(CYW43_WL_GPIO_LED_PIN), "Failed to turn LED on");
}