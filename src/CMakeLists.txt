cmake_minimum_required(VERSION 3.19)

add_library(${CMAKE_PROJECT_NAME} STATIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/dool.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/transform.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tree.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/cellmap.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/readfile.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/util.cpp
)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/include")