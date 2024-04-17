#pragma once

#include <iostream>
#include <cstdbool>
#include <fstream>
#include <sstream>
#include <vector>

// opengl lib
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// math lib
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "WindowApp.hpp"

#define HEIGHT 720
#define WIDTH 1280


/*shaders*/
GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);