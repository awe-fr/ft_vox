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
		glm::mat4		_Projection;
		glm::mat4		_Model;
		glm::mat4		_View;
	public:
        Skybox(void);
        ~Skybox(void);
		unsigned int	GiveCubemapTexture();
		unsigned int	GiveVAO();
		glm::mat4		GiveProjection();
		glm::mat4		GiveModel();
		glm::mat4		GiveView();
		void			SetProjection(glm::mat4 NewProjection);
		void			SetView(glm::mat4 NewView);
};