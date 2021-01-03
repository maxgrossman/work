cmake_minimum_required(VERSION 3.10)
project(hacker_rank_dyanmic_arrays)

include_directories(../include)
set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/dyanmic_array.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/hacker_rank_dynamic_arrays.cpp
)

add_executable(answer ${SOURCES})
