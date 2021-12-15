cmake_minimum_required(VERSION 3.14) # I don't actually have a good reason to use 3.14 but pi is pretty cool and this seems to work so...

project(substd_test)

include_directories(../include)

add_executable(compile_time_test compile_time_test.cpp)
add_executable(vec_test vec_test.cpp)

