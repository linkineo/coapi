CMAKE_MINIMUM_REQUIRED(VERSION 3.0.0)

project(coap-on-mcu)
find_package(Boost REQUIRED)

add_definitions(-std=c++11)
add_executable(coap-on-mcu main.cpp)
