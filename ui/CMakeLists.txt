
include_directories(
        ../3dparty/imgui/
        ../gl/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set ( HEAD include/imgui_fs.h include/imgui_log.h include/imgui_popup.h include/imgui_baseapp.h include/imgui_abstractwindow.h)
set ( SRC src/imgui_fs.cpp src/imgui_log.cpp src/imgui_popup.cpp src/imgui_baseapp.cpp)


add_library(bsl_ui ${HEAD} ${SRC})
target_link_libraries(bsl_ui bsl_gl imgui ${NEED_LIBS})