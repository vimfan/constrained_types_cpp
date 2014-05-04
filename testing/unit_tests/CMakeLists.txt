add_executable(
    unit_tests
    tests.cpp
    constraints.cpp
)

include_directories(../..)

target_link_libraries(
    unit_tests
    gtest
    gtest_main
    gmock
    pthread
)

add_test(run_unit_tests unit_tests)
