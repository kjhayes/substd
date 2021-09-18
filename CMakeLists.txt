cmake_minimum_required(VERSION 3.10.2)

project(substd)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

install(TARGETS substd LIBRARY)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/${CMAKE_PROJECT_NAME} TYPE INCLUDE)
