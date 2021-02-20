cmake_minimum_required(VERSION 3.10)
project(hashtable)
include_directories(include)
set (SOURCES
    ${SOURCES}
    src/test.cpp
)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
add_executable(test ${SOURCES})
