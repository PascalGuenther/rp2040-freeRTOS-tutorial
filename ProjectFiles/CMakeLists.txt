add_executable(freeRTOS-RP2040-blink
  main.c
)

target_link_libraries(freeRTOS-RP2040-blink PUBLIC
  pico_stdlib
  freertos
)

pico_enable_stdio_usb(freeRTOS-RP2040-blink 1)
pico_enable_stdio_uart(freeRTOS-RP2040-blink 0)

pico_add_extra_outputs(freeRTOS-RP2040-blink)
