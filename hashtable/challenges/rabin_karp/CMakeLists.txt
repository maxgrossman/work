cmake_minimum_required(VERSION 3.10)
project(karp_raven)
set (SOURCES
    ${SOURCES}
    ./rabin_karp.cpp
)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
add_executable(rabin_karp ${SOURCES})
