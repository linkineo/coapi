cmake_minimum_required(VERSION 2.8.0)

project(coapi_test)

add_definitions(-std=c++11)
include_directories(cantcoap ${CMAKE_SOURCE_DIR}/test)

add_executable(coapi_test test.cpp)
