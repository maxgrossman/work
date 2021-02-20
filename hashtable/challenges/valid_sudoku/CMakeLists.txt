cmake_minimum_required(VERSION 3.10)
project(valid_sudoku)
include_directories(../../include)
set (SOURCES
    ${SOURCES}
    src/valid_sudoku.cpp
)

set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
add_executable(valid_sudoku ${SOURCES})
