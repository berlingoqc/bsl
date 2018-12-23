#include_directories("${PROJECT_SOURCE_DIR}/wutils/")

add_executable(test_vfs local_fs.cpp)
target_link_libraries(test_vfs bsl_vfs Catch2::Catch2)


file( COPY root_test DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
include(CTest)
include(Catch)
catch_discover_tests(test_vfs)