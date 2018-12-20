#pragma once

// Import des header de opengl
#ifdef EMSCRIPTEN

#include <emscripten/emscripten.h>
#include <emscripten/fetch.h>
#define GLFW_INCLUDE_ES3
#include <GLFW/glfw3.h>
#include <GLES3/gl3.h>


#include <filesystem>

#define SHADER_VERSION "#version 300 es"

namespace fs = std::filesystem;

#define END_PROGRAM(code) emscripten_force_exit(code)

#else

#include <filesystem>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace fs = std::filesystem;

#define SHADER_VERSION "#version 430 core"
#define END_PROGRAM(code) printf("End of program goodbye\n"); return

#endif

// import les trucs de math
#include <glm/glm.hpp>
#include <glm/trigonometric.hpp>    // sin , cos , radians ...
#include <glm/gtc/matrix_transform.hpp>
#include <glm/exponential.hpp>      // pow , log, exp2, sqrt, ...
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>



// Import des autres headers 
#include <cstring>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include <random>

typedef unsigned int uint;



