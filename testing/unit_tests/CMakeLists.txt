add_executable(
    unit_tests
    tests.cpp
    constraints.cpp
)

target_link_libraries(
    unit_tests
    gtest
    gtest_main
    gmock
    pthread
)

include_directories(../..)

if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-g -O0 --coverage -fprofile-arcs -ftest-coverage")
endif()

add_test(run_unit_tests unit_tests)
