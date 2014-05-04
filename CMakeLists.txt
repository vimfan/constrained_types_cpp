cmake_minimum_required(VERSION 2.8)
project(constrained_types)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")

enable_testing()
add_subdirectory(testing)
