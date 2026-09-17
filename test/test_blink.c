#include "test_blink.h"

// Test turning the LED off
void test_led_off() {
    write_led(0);
    TEST_ASSERT_FALSE_MESSAGE(cyw43_arch_gpio_get(CYW43_WL_GPIO_LED_PIN), "Failed to turn LED off");
}

// Test turning the LED on
void test_led_on() {
    write_led(1);
    TEST_ASSERT_TRUE_MESSAGE(cyw43_arch_gpio_get(CYW43_WL_GPIO_LED_PIN), "Failed to turn LED on");
}

// Test that the logic used to drive the LED's state increments count correctly
void test_led_state_counter() {
    // Actual starting conditions
    bool state = 0;
    int count = 0;
    int last_count = 0;

    // Test over slightly more than two cycles
    for (int i=0; i < 24; i++) {
        // Run the LED driver logic
        do_led_logic(&count, &state);

        // `count` should increase by one each time
        TEST_ASSERT_EQUAL_INT_MESSAGE(last_count + 1, count, "LED logic driver failed to increment count correctly");

        // Save the value of count prior to running the next test
        last_count = count;
    }
}

// Test the 'flip 10 times out of 11' logic used to drive the LED
void test_led_states() {
    // What the next state should be (according to the original logic) for a sequence of
    // incremental counts starting at 0 with an initial LED value of 0
    const uint8_t expected_next_state[] = {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1};

    // Define starting point as expected above
    bool state = 0;

    // Space to hold actual outputs
    uint8_t actual_next_state[NUM_ELEM(expected_next_state)] = {0};

    // Capture the outputs
    for (int i=0; i < NUM_ELEM(expected_next_state); i++) {
        // Force the count to the expected value for every test (this test is independent of count)
        int count = i;

        // Capture the logic output
        do_led_logic(&count, &state);
        actual_next_state[i] = (uint8_t)state;
    }

    TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE(expected_next_state, actual_next_state, NUM_ELEM(expected_next_state), "LED output sequence doesn't match the baseline");
}