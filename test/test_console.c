#include "test_console.h"
#include "console.h"
#include "unity.h"

// Test switching case from lowercase to uppercase
void test_console_toUppercase(void)
{
	char expected = 'A';

	for (char c = 'a'; c <= 'z'; c++) {
		char actual = switch_case(c);
		TEST_ASSERT_TRUE_MESSAGE(actual == expected, "Failed to set char to uppercase");

		expected++;
	}
}

// Test switching case from uppercase to lowercase
void test_console_toLowercase(void)
{
	char expected = 'a';

	for (char c = 'A'; c <= 'Z'; c++) {
		char actual = switch_case(c);
		TEST_ASSERT_TRUE_MESSAGE(actual == expected, "Failed to set char to lowercase.");

		expected++;
	}
}

// Test returning the same char for a non-alphabetic input char
void test_console_notAlpha(void)
{
	char c = '&';
	char expected = '&';
	char actual = switch_case(c)

	TEST_ASSERT_TRUE_MESSAGE(actual == expected, "Failed to return non-alphabetic char.");
}
