add_executable(performance_tests tests.cpp)
target_link_libraries(performance_tests gtest gtest_main pthread)
add_test(run_tests performance_tests)
