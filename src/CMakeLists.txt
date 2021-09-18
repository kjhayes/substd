cmake_minimum_required(VERSION 3.10.2)

add_library(substd STATIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/dool.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/transform.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tree.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/cellmap.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/readfile.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/util.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/itransformable.cpp
)

target_include_directories(substd PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
