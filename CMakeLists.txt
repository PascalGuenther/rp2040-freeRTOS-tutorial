cmake_minimum_required(VERSION 3.12)

include(${CMAKE_CURRENT_SOURCE_DIR}/pico_sdk_import.cmake)

project(Pico-FreeRTOS)

pico_sdk_init()

add_subdirectory(freertos)
add_subdirectory(ProjectFiles)