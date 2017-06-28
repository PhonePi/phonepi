cmake_minimum_required(VERSION 3.7)
project(desktop-pi)

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

add_executable(desktop-pi main.cpp Config.cpp AppRunner.cpp)
target_link_libraries(desktop-pi inih)

qt5_use_modules(desktop-pi Widgets)

install(TARGETS desktop-pi EXPORT desktop-pi DESTINATION bin)

