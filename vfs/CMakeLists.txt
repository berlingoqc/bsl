
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(test)

add_library(bsl_vfs include/vfs.h src/vfs_local.cpp)
target_link_libraries(bsl_vfs ${NEED_LIBS})