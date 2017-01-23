cmake_minimum_required(VERSION 3.0.0)

project(coapy_test)

add_definitions(-std=c++11)
include_directories(cantcoap)

add_executable(coapy_test test.cpp)
