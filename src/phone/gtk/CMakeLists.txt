cmake_minimum_required(VERSION 3.5)
project(phone)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES main.cpp Phone.cpp Phone.h Call.cpp Call.h lib.h)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

find_package(PkgConfig REQUIRED)
find_package (Qt5 CONFIG REQUIRED DBus)

pkg_check_modules(GTKMM gtkmm-3.0)

link_directories(${GTKMM_LIBRARY_DIRS})
include_directories(${GTKMM_INCLUDE_DIRS})

add_executable(phone ${SOURCE_FILES})

target_link_libraries(phone ${GTKMM_LIBRARIES} Qt5::DBus)
