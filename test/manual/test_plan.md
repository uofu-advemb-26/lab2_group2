# Manual Test Plan
## Setup
1. Obtain two Wireless RP2040 Raspberry Pi Picos with headers.
2. Flash the debugging software to one of the Picos and connect the two picos using the instructions in Appendix A of the [Raspberry Pi Pico Getting Started Guide](https://pip-assets.raspberrypi.com/categories/610-raspberry-pi-pico/documents/RP-008276-DS-2-getting-started-with-pico.pdf).
3. Setup your development enviroment using [these instructions](https://github.com/uofu-embed/rtos/blob/main/SETUP.md). Both the Pico SDK and the FreeRTOS kernel should be downloaded outside of this repository with the enviroment variables set so this build system can find them.
4. From the root directory of this repository, initialize CMake using:
    1. `mkdir build`
    2. `cmake -B build -S .`
5. Build the project using:
    1. `cmake --build build`
6. Flash the executable to the Pico using:
    1. `cmake --build build --target openocd_test`
7. Open a terminal connection to the Pico using:
    1. `sudo minicom -D /dev/ttyACM0 -b 115200`
8. Follow each step from *Steps and Expected Behavior* sequentially and compare results to the expected results indicated.

## Steps and Expected Behavior
1. Observe the Pico's onboard LED.
    - Expected Result: it turns on and off following the pattern `SHORT_OFF, SHORT_ON, SHORT_OFF, SHORT_ON, SHORT_OFF, SHORT_ON, SHORT_OFF, SHORT_ON, SHORT_OFF, SHORT_ON, LONG_OFF, SHORT_ON, ...`
2. Time the duration of `SHORT_OFF` using a stopwatch.
    - Expected Result: `SHORT_OFF` has a duration of approximately 0.5 seconds.
3. Time the duration of `SHORT_ON` using a stopwatch.
    - Expected Result: `SHORT_ON` has a duration of approximately 0.5 seconds.
4. Time the duration of `LONG_OFF` using a stopwatch.
    - Expected Result: `LONG_OFF` has a duration of approximately 1.0 second.
5. Type characters in the terminal connection to the Pico.
    - Expected Result: The LED continues to flash with the same pattern at the same rate.
6. < add console test cases here >