cmake_minimum_required(VERSION 3.26)
project(Tetris)

set(CMAKE_CXX_STANDARD 17)

add_executable(Tetris main.cpp
        draw.h
        draw.cpp
        tetris.h
        tetris.cpp)
