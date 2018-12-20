cmake_minimum_required(VERSION 3.8)

project("bsl")

set(CMAKE_CXX_STANDARD 17)

if(UNIX)
    set( NEED_LIBS stdc++fs pthread )
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    add_definitions(-DEMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    set( EM_TARGET_PROP "--emrun   -s WASM=1 -std=c++11 -s DISABLE_EXCEPTION_CATCHING=0 -s ALLOW_MEMORY_GROWTH=1 -s USE_WEBGL2=1 -s FULL_ES3=1 -s USE_GLFW=3 -s FETCH=1 -")
else()

endif()

find_package(Catch2 REQUIRED)

enable_testing()

add_subdirectory(3dparty/imgui)

add_subdirectory(bsl)
add_subdirectory(vfs)
add_subdirectory(thread)
add_subdirectory(ui)
add_subdirectory(gl)