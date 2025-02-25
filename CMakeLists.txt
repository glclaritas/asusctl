cmake_minimum_required(VERSION 3.10)

project(asusctl VERSION 0.0.1)

# set cmake standard 
set(CMAKE_C_STANDARD 99)

# find dbus
find_package(PkgConfig REQUIRED)
pkg_check_modules(DBUS REQUIRED dbus-1)

# source
set(SOURCES main.c)

# output
add_executable(asusctl ${SOURCES})

# includes
include_directories(
    ${DBUS_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/src
)

# link dbus
target_link_libraries(asusctl ${DBUS_LIBRARIES})
