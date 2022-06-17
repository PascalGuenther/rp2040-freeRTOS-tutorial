set(PROJECT_FREERTOS_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/FreeRTOS-Kernel)

add_library(freertos INTERFACE)
target_sources(freertos INTERFACE
    ${PROJECT_FREERTOS_SOURCE}/event_groups.c
    ${PROJECT_FREERTOS_SOURCE}/list.c
    ${PROJECT_FREERTOS_SOURCE}/queue.c
    ${PROJECT_FREERTOS_SOURCE}/stream_buffer.c
    ${PROJECT_FREERTOS_SOURCE}/timers.c
    ${PROJECT_FREERTOS_SOURCE}/tasks.c
    ${PROJECT_FREERTOS_SOURCE}/portable/MemMang/heap_3.c
    ${PROJECT_FREERTOS_SOURCE}/portable/GCC/ARM_CM0/port.c
)

target_include_directories(freertos INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_FREERTOS_SOURCE}/include
    ${PROJECT_FREERTOS_SOURCE}/portable/GCC/ARM_CM0
)
