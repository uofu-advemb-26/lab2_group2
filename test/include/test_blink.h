#ifndef _TEST_BLINK_H_
#define _TEST_BLINK_H_

#include <stdio.h>
#include <pico/stdlib.h>
#include <stdint.h>
#include "blink.h"
#include "unity.h"

#define NUM_ELEM(array) (sizeof(array) / sizeof(array[0]))

void test_led_off();
void test_led_on();
void test_led_states();

#endif