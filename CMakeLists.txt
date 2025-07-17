cmake_minimum_required(VERSION 3.10)

project(asusctl VERSION 0.0.1)

# set cmake standard 
set(CMAKE_C_STANDARD 99)

# source
set(SOURCES
    src/main.c
    src/cpumode.c
    src/fanmode.c
)

# output
add_executable(asusctl ${SOURCES})

target_include_directories(asusctl PRIVATE src)
