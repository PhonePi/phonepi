cmake_minimum_required(VERSION 3.7)
project(unblock-pi)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp Config.cpp UnblockExecutor.cpp Timer.cpp)

find_package(Threads)
# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)
# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# add inih
add_subdirectory(inih)
include_directories(inih/cpp)

# Widgets finds its own dependencies.
find_package(Qt5Widgets REQUIRED)
find_package(Qt REQUIRED)

add_executable(unblock-pi ${SOURCE_FILES})
target_link_libraries(unblock-pi inih)
target_link_libraries(unblock-pi ${CMAKE_THREAD_LIBS_INIT})
qt5_use_modules(unblock-pi  Widgets)

install(TARGETS unblock-pi EXPORT unblock-pi DESTINATION bin)
