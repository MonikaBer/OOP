cmake_minimum_required(VERSION 3.6)
project(menu)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})


set(CMAKE_CXX_STANDARD 14)

add_executable(menu src/main.cpp src/menu.cpp)
target_include_directories(menu PUBLIC inc)
target_link_libraries(menu ${CURSES_LIBRARIES})
