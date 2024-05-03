#pragma once 

#include "Major.h"

// float	Vertex[] = {
// 	-1.0f, -1.0f, 1.0f,
// 	 1.0f, -1.0f, 1.0f,
// 	 1.0f, -1.0f, -1.0f,
// 	-1.0f, -1.0f, -1.0f,
// 	-1.0f, 1.0f, 1.0f,
// 	 1.0f, 1.0f, 1.0f,
// 	 1.0f, 1.0f, -1.0f,
// 	-1.0f, 1.0f, -1.0f,
// };

// unsigned int	UV[] = {
// 	1, 2, 6,
// 	6, 5, 1,

// 	0, 4, 7,
// 	7, 3, 0,

// 	4, 5, 6,
// 	6, 7, 4,

// 	0, 3, 2,
// 	2, 1, 0,

// 	0, 1, 5,
// 	5, 4, 0,

// 	3, 7, 6,
// 	6, 2, 3,
// };

class	Skybox {
	private:
		unsigned int	_CubemapTexture;
		unsigned int	_VAO;
		unsigned int	_VBO;
		unsigned int	_EBO;
		// unsigned int	_UV;
		// float			_Vertex;
	public:
		unsigned int	GiveCubemapTexture();
		unsigned int	GiveVAO();
		void			init();
};