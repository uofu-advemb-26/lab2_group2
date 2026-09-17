#include "blink.h"

void blink_task(__unused void *params) {
    // Initialize the green LED (that's controlled by the wireless module)
    hard_assert(cyw43_arch_init() == PICO_OK);

    int count = 0;
    bool on = false;

    // Flash the LED with about 0.5 seconds on and 0.5 seconds off
    while (true) {
        // Commit state to the LED
        write_led(on);

        // Update the state
        do_led_logic(&count, &on);

        // 500ms delay (parameter is in ticks, but FreeRTOS on the Pico is configured for 1 tick per ms)
        vTaskDelay(500);
    }
}

// Flip the LED state 10 times out of 11
void do_led_logic(int *count, bool *state) {
    if ((*count)++ % 11) {
        *state = !(*state);
    }
}

// Write a value to the onboard LED
void write_led(const bool state) {
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, state);
}

// Create the blink task with a higher priority
void create_blink_task(void) {
    xTaskCreate(blink_task, "BlinkThread",
                BLINK_TASK_STACK_SIZE, NULL, BLINK_TASK_PRIORITY, NULL);
}