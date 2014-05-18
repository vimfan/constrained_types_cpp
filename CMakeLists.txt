cmake_minimum_required(VERSION 2.8)
project(constrained_types)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

enable_testing()
add_subdirectory(external/gmock)

include_directories(external/gmock/include external/gmock/gtest/include)
add_subdirectory(testing)

