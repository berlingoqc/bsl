add_executable(test_thread thread_test.cpp)
target_link_libraries(test_thread bsl_thread Catch2::Catch2)

include(CTest)
include(Catch)
catch_discover_tests(test_thread)