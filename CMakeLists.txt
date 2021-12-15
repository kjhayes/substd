cmake_minimum_required(VERSION 3.14)

project(substd)

enable_testing()

if(CMAKE_PROJECT_NAME STREQUAL substd)
    include(CTest)
endif()

if(CMAKE_PROJECT_NAME STREQUAL substd AND BUILD_TESTING)
    add_subdirectory(./tests/)
endif()