cmake_minimum_required(VERSION 3.10)
project(hacker_rank_dyanmic_arrays)

include_directories(../include)
set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/linked_list.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/add_linked_list_numbers.cpp
)

add_executable(answer ${SOURCES})
