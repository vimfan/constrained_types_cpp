add_executable(
    utils_tests
    utils_test.cpp
)

include_directories(../..)

target_link_libraries(
    utils_tests
    gtest
    gtest_main
    gmock
    pthread
)

add_test(run_unit_tests utils_tests)
