cmake_minimum_required(VERSION 3.19)

project(substd)

add_subdirectory(${CMAKE_SOURCE_DIR}/src)

install(TARGETS ${CMAKE_PROJECT_NAME} LIBRARY)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/${CMAKE_PROJECT_NAME} TYPE INCLUDE)