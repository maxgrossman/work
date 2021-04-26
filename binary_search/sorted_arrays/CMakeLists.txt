cmake_minimum_required(VERSION 3.10)
project(karp_raven)
set (SOURCES
    ${SOURCES}
    ./bin_search_array.cpp
)
set (CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
add_executable(bin_search_array ${SOURCES})
