# CMakeList.txt : projet CMake pour crazygl, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required (VERSION 3.8)

find_package(OpenGL REQUIRED)

set(GLEW_INCLUDE_PATH "" CACHE PATH "The directory that contains GL/glew.h" )
set(GLEW_LIBRARY "" CACHE PATH "libglew.a or glew.lib" )

set(GLM_INCLUDE_PATH "" CACHE PATH "The directory that contains glm/glm.hpp" )

set(GLFW_INCLUDE_PATH "" CACHE PATH "The directory that contains GLFW/glfw3.h" )
set(GLFW_LIBRARY "" CACHE PATH "The directory that contains glfw3.lib" )

set(SOIL_INCLUDE_PATH "" CACHE PATH "The directory that contains SOIL.h" )
set(SOIL_LIBRARY "" CACHE PATH "The directory that contains SOIL.lib" )

set(ASSIMP_INCLUDE_PATH "" CACHE PATH "The directory that contains assimp/assimp.h" )
set(ASSIMP_LIBRARY "" CACHE PATH "The directory that contains assimp.lib" )


if(UNIX)
	set( GL_LIBS GL GLEW glfw assimp SOIL)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
	set( GL_LIBS GL GLEW glfw libassimp soil)
else() #windows
	set( GL_LIBS glew32d glfw3 SOIL assimp-vc140-mt)
endif()

include_directories(
	${GLEW_INCLUDE_PATH}
	${GLFW_INCLUDE_PATH}
	${GLM_INCLUDE_PATH}
	${SOIL_INCLUDE_PATH}
	${ASSIMP_INCLUDE_PATH}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

link_directories(
	${GLEW_LIBRARY}
	${ASSIMP_LIBRARY}
	${GLFW_LIBRARY}
	${SOIL_LIBRARY}
)

SET( HEAD  include/header.h include/shaders.h include/textures.h )
SET( SRC src/shaders.cpp src/textures.cpp )

# Ajoutez une source à l'exécutable de ce projet.
add_library (bsl_gl ${HEAD} ${SRC})
target_link_libraries(bsl_gl ${GL_LIBS} ${NEED_LIBS})
