cmake_minimum_required(VERSION 3.1)

project(Extra_Tetris)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(raylib REQUIRED)

add_executable(tetris main/main.cc)
target_link_libraries(tetris raylib)