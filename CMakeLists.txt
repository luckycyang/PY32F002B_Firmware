cmake_minimum_required(VERSION 3.20)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_C_COMPILER "/usr/bin/arm-none-eabi-gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/arm-none-eabi-g++")
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
set(ASM_OPTIONS "-x assembler-with-cpp")
set(CMAKE_ASM_COMPILER ${CMAKE_C_COMPILER} ${ASM_FLAGS})

set(FLAGS -nostdlib)
# set(COMPILER_FLAGS -mcpu=cortex-m0plus -mthumb -mno-thumb-interwork)
add_compile_options(-mcpu=cortex-m0plus -mthumb)

add_definitions(-DPY32F002Bx5)

add_subdirectory(lib)

project(embed C ASM CXX)
add_executable(${PROJECT_NAME})
set_property(
  SOURCE startup/startup_py32f002bxx.s
  APPEND
  PROPERTY COMPILE_OPTIONS -x assembler-with-cpp)
target_sources(${PROJECT_NAME} PRIVATE src/main.c startup/startup.c)

target_link_options(${PROJECT_NAME} PRIVATE -T
                    ${PROJECT_SOURCE_DIR}/py32f002bx5.ld ${FLAGS})

target_compile_options(${PROJECT_NAME} PRIVATE ${FLAGS} ${COMPILER_FLAGS})

target_link_libraries(${PROJECT_NAME} PRIVATE Device HAL BSP)

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/inc)
