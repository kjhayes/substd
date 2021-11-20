cmake_minimum_required(VERSION 3.10.2)

add_library(substd STATIC)

target_include_directories(substd PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
