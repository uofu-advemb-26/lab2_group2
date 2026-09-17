include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

add_executable(test_all
  test_main.c
  test_blink.c
  ../src/blink.c
  test_console.c
  ../src/console.c
  unity_config.c
)

target_link_libraries(test_all PRIVATE
  pico_stdlib
  pico_async_context_freertos
  FreeRTOS-Kernel-Heap4
  unity
)

# The CYW43 is the Wifi/Bluetooth module. If the board is set to pico_w, this
# variable will be set and the wireless libraries added.
if(PICO_CYW43_SUPPORTED)
    target_link_libraries(test_all PRIVATE
        pico_cyw43_arch_none
    )
endif()

# Modify the below lines to enable/disable output over UART/USB.
# These are mutually exclusive, only set one.
pico_enable_stdio_uart(test_all 1)
pico_enable_stdio_usb(test_all 0)

# This will speed up the simulation, since data won't be copied from the flash controller.
# It does make the binary non-persistent on a real microcontroller.
# pico_set_binary_type(test_all no_flash)

find_program(RENODE renode
# This is extra stuff so it can find the mac installation paths.
 NAMES macos_run.command Renode.exe
 PATHS /Applications/Renode.app/Contents/MacOS)

set(RENODE_FLAGS
  --disable-xwt
  --port -2
  --pid-file renode.pid
  --console
  )

add_test(NAME simulate_test_all COMMAND
    ${RENODE}
     ${RENODE_FLAGS}
    -e "$ELF=@$<TARGET_FILE:test_all>; $WORKING=@${CMAKE_SOURCE_DIR}; include @${CMAKE_SOURCE_DIR}/test/simulate.resc; start"
    )


find_program(OPENOCD openocd)
find_program(PICOTOOL picotool)

add_custom_target(flash_test ${PICOTOOL} load -f $<TARGET_FILE:test_all> DEPENDS test_all)
add_custom_target(openocd_test ${OPENOCD} -s ${OPENOCD_PATH} -f interface/cmsis-dap.cfg -f target/rp2040.cfg -c 'adapter speed 5000' -c 'program "$<TARGET_FILE:test_all>" verify reset exit' DEPENDS test_all)

