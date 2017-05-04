cmake_minimum_required(VERSION 3.7)
project(daemon)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES main.cpp)

find_package(PkgConfig REQUIRED)
find_package (Qt5 CONFIG REQUIRED DBus)

add_executable(daemon ${SOURCE_FILES})

target_link_libraries(daemon Qt5::DBus)