cmake_minimum_required(VERSION 3.10)
project(linked_head_tail)
include_directories(../../linked_list/include include)
file(GLOB SOURCES "src/*.cpp")
set(SOURCES
    ../../linked_list/src/linked_list.cpp
    ${SOURCES}
)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
add_executable(test ${SOURCES})
