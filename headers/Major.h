#pragma once

#include <iostream>
#include <cstdbool>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

// opengl lib
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// math lib
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "WindowApp.hpp"
#include "PlayerInfo.hpp"
#include "Chunk.hpp"

#define HEIGHT 720
#define WIDTH 1280


/*shaders*/
GLuint  LoadShaders(const char * vertex_file_path,const char * fragment_file_path);