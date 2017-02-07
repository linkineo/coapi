CMAKE_MINIMUM_REQUIRED(VERSION 2.8.0)

project(coapi)

option(USE_EXTERNAL_BOOST "Use external Boost library" OFF)

if(USE_EXTERNAL_BOOST)
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
else()
include_directories(${CMAKE_SOURCE_DIR}/deps)
endif()

include_directories(${CMAKE_SOURCE_DIR}/coapi)

add_definitions(-std=c++11)
add_definitions(-ftemplate-depth-500)
add_executable(coapi example.cpp)

add_subdirectory(test)

enable_testing()
add_test(frame_parser test/coapi_test)

