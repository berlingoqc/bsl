
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

#add_subdirectory(test)

#set ( HEAD include/definiton.h include/chrono.h )
set ( SRC src/chrono.cpp)

add_library(bsl ${HEAD} ${SRC})
target_link_libraries(bsl ${NEED_LIBS})