CMAKE_MINIMUM_REQUIRED(VERSION 3.0.0)

project(coap-on-mcu)
find_package(Boost REQUIRED)

include_directories(${CMAKE_SOURCE_DIR})

add_definitions(-std=c++11)
add_executable(coap-on-mcu main.cpp)

add_subdirectory(test)

enable_testing()
add_test(frame_parser test/coapy_test)

