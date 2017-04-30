cmake_minimum_required(VERSION 3.5)
project(phone)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Phone.cpp Phone.h Number.cpp Number.h lib.h)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

link_directories(${GTKMM_LIBRARY_DIRS})
include_directories(${GTKMM_INCLUDE_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER})

add_executable(phone ${SOURCE_FILES})

target_link_libraries(phone ${GTK3_LIBRARIES} ${GTKMM_LIBRARIES})