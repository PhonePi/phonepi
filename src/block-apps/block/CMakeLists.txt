cmake_minimum_required(VERSION 3.7)
project(block-pi)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp)

# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)
# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Widgets finds its own dependencies.
find_package(Qt5Widgets REQUIRED)
find_package(Qt REQUIRED)

add_executable(block-pi ${SOURCE_FILES})
qt5_use_modules(block-pi  Widgets)

install(TARGETS block-pi EXPORT block-pi DESTINATION bin)
