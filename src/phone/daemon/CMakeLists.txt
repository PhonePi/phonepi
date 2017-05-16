cmake_minimum_required(VERSION 3.7)
project(daemon)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES main.cpp Handler.cpp Handler.h Struct.h)

find_package(PkgConfig REQUIRED)
find_package (Qt5 CONFIG REQUIRED DBus)

add_executable(calls_daemon ${SOURCE_FILES})

target_link_libraries(calls_daemon Qt5::DBus)
