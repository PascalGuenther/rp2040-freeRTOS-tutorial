add_executable(freeRTOS-RP2040-blink
  main.c
)

target_link_libraries(freeRTOS-RP2040-blink PUBLIC
  pico_stdlib
  freertos
)

pico_add_extra_outputs(freeRTOS-RP2040-blink)
