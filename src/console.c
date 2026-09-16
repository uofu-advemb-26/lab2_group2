#include "console.h"

char switch_case(char c)
{
    if (c <= 'z' && c >= 'a') return c - 32; // Switch to uppercase
    else if (c >= 'A' && c <= 'Z') return c + 32; // Switch to lowercase
    else return c; // No flips on non-alphabetical characters
}

void main_task(__unused void *params)
{
    // Copy any input characters to output and flip their case (lowercase -> uppercase; uppercase -> lowercase)
    char c;
    while(c = getchar()) {
        putchar(switch_case(c));
    }
}

