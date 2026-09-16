#include "blink.h"

int count = 0;
bool on = false;

void blink_task(__unused void *params) {
    // Initialize the green LED (that's controlled by the wireless module)
    hard_assert(cyw43_arch_init() == PICO_OK);

    // Flash the LED with about 0.5 seconds on and 0.5 seconds off
    while (true) {
        // Write to the LED
        write_led(on);

        // Probably a bug; LED state flips 9 times out of 10
        if (count++ % 11) on = !on;

        // 500ms delay (parameter is in ticks, but FreeRTOS on the Pico is configured for 1 tick per ms)
        vTaskDelay(500);
    }
}

void write_led(const bool state) {
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, state);
}

void create_blink_task(void) {
    // Create the blink task with a higher priority
    xTaskCreate(blink_task, "BlinkThread",
                BLINK_TASK_STACK_SIZE, NULL, BLINK_TASK_PRIORITY, NULL);
}