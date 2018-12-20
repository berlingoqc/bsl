include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/bsl/include
)

add_subdirectory(test)

set ( HEAD include/log_lock.h include/queue.h include/runnable.h )
set ( SRC src/queue.cpp)

add_library(bsl_thread ${HEAD} ${SRC})
target_link_libraries(bsl_thread bsl ${NEED_LIBS})