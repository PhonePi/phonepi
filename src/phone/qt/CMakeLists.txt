cmake_minimum_required(VERSION 3.7)
project(dialer-pi)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp DialerWindow.h DialerWindow.cpp
        Button.cpp Button.h CallWindow.cpp CallWindow.h)

# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)
# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Widgets finds its own dependencies.
find_package(Qt5Widgets REQUIRED)
find_package(Qt5DBus REQUIRED)
find_package(Qt REQUIRED)

add_executable(dialer-pi ${SOURCE_FILES})
qt5_use_modules(dialer-pi  Widgets)
qt5_use_modules(dialer-pi  DBus)

install(TARGETS dialer-pi EXPORT dialer-pi DESTINATION bin)
