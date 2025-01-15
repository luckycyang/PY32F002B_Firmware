cmake_minimum_required(VERSION 3.20)

project(CMSIS)
add_library(CMSIS INTERFACE)
target_include_directories(CMSIS INTERFACE ./CMSIS/Include)

project(Device)
add_library(Device STATIC ./CMSIS/Device/PY32F0xx/Source/system_py32f0xx.c)
target_include_directories(Device PUBLIC ./CMSIS/Device/PY32F0xx/Include)
target_link_libraries(Device PUBLIC CMSIS)

project(BSP)
add_library(BSP STATIC ./BSP/PY32F002Bxx_Start_Kit/py32f002bxx_Start_Kit.c
                       ./BSP/PY32F002Bxx_Start_Kit/py32f002bxx_ll_Start_Kit.c)
target_include_directories(BSP PUBLIC ./BSP/PY32F002Bxx_Start_Kit)
target_link_libraries(BSP PRIVATE HAL Device HAL_CONF)

project(HAL_CONF)
add_library(HAL_CONF INTERFACE)
target_include_directories(HAL_CONF INTERFACE ./inc)

file(GLOB HAL_SOURCES ./PY32F002B_HAL_Driver/Src/*.c)
project(HAL)
add_library(HAL STATIC ${HAL_SOURCES})
target_include_directories(HAL PUBLIC ./PY32F002B_HAL_Driver/Inc)
target_link_libraries(HAL PUBLIC Device HAL_CONF)
