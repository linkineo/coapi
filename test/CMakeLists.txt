cmake_minimum_required(VERSION 2.8.0)

project(coapi_test)


add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)
add_definitions(-std=c++11)
include_directories(cantcoap ${CMAKE_SOURCE_DIR}/test)

add_executable(coapi_test test.cpp)

if(ONLINE_TESTS)
find_package(Threads)
add_executable(coapi_online_test online_test.cpp)
target_link_libraries(coapi_online_test ${CMAKE_THREAD_LIBS_INIT})
endif()
