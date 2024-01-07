cmake_minimum_required(VERSION 3.13)

include(cmake/pico_sdk_import.cmake)
include(cmake/CPM.cmake)

project(pico-tcp-wave C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

pico_sdk_init()

CPMAddPackage(
    NAME pico_usbnet
    GIT_REPOSITORY "https://github.com/brunobasto/pico-usbnet.git"
    GIT_TAG "main"
)

CPMAddPackage(
    NAME pico_adc
    GIT_REPOSITORY "https://github.com/brunobasto/pico-adc.git"
    GIT_TAG "main"
)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/debug.cpp
    src/wave.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    pico_stdlib
    pico_adc
    pico_usbnet
)

pico_enable_stdio_usb(${PROJECT_NAME} 0)
pico_enable_stdio_uart(${PROJECT_NAME} 0)
pico_add_extra_outputs(${PROJECT_NAME})

target_compile_definitions(${PROJECT_NAME} PRIVATE PICO_ENTER_USB_BOOT_ON_EXIT=1)
