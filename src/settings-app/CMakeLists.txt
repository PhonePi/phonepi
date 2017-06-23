cmake_minimum_required(VERSION 3.7)
project(settings-pi)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp brightness.h brightness.cpp)

find_package(Threads)
# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)
# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Widgets finds its own dependencies.
find_package(Qt5Widgets REQUIRED)
find_package(Qt REQUIRED)

add_executable(settings-pi ${SOURCE_FILES})
qt5_use_modules(settings-pi  Widgets)
target_link_libraries(settings-pi ${CMAKE_THREAD_LIBS_INIT})

install(TARGETS settings-pi EXPORT settings-pi DESTINATION bin)
install(FILES entry/settings-pi.desktop
        DESTINATION $ENV{HOME}/.local/share/applications
        PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ GROUP_WRITE WORLD_READ WORLD_WRITE)
install(FILES entry/settings-pi.png
        DESTINATION $ENV{HOME}/.local/share/icons
        PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ GROUP_WRITE WORLD_READ WORLD_WRITE)
