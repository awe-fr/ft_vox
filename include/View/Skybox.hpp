#pragma once 

#include "ViewVars.hpp"
#include <string>
#include <iostream>
#include "stb_image.h"

class	Skybox {
	private:
		unsigned int	_CubemapTexture;
		unsigned int	_VAO;
		unsigned int	_VBO;
		unsigned int	_EBO;
		// unsigned int	_UV;
		// float			_Vertex;
	public:
        Skybox(void);
        ~Skybox(void);
		unsigned int	GiveCubemapTexture();
		unsigned int	GiveVAO();
};