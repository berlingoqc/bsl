

include_directories(
    ${PROJECT_SOURCE_DIR}/3dparty/imgui/
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set ( HEAD include/imgui_fs.h include/imgui_log.h include/imgui_popup.h )
set ( SRC src/imgui_fs.cpp src/imgui_log.cpp src/imgui_popup.cpp )


add_library(bsl_ui ${HEAD} ${SRC})
target_link_libraries(bsl_ui imgui ${NEED_LIBS})