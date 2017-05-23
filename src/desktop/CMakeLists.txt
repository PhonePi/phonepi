cmake_minimum_required(VERSION 3.7)
project(desktop)

set(CMAKE_CXX_STANDARD 14)

# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)
# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Widgets finds its own dependencies.
find_package(Qt5Widgets REQUIRED)
find_package(Qt REQUIRED)

add_subdirectory(inih)
include_directories(inih/cpp)

add_executable(desktop main.cpp Config.cpp)
target_link_libraries(desktop inih)

qt5_use_modules(desktop Widgets)