#include <View/Skybox.hpp>

float	Vertex[] = {
	-1.0f, -1.0f, 1.0f,
	 1.0f, -1.0f, 1.0f,
	 1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f, 1.0f, 1.0f,
	 1.0f, 1.0f, 1.0f,
	 1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
};

unsigned int	UV[] = {
	1, 2, 6,
	6, 5, 1,

	0, 4, 7,
	7, 3, 0,

	4, 5, 6,
	6, 7, 4,

	0, 3, 2,
	2, 1, 0,

	0, 1, 5,
	5, 4, 0,

	3, 7, 6,
	6, 2, 3,
};

Skybox::Skybox(void) {
	glGenVertexArrays(1, &this->_VAO);
	glGenBuffers(1, &this->_VBO);
	glGenBuffers(1, &this->_EBO);
	glBindVertexArray(this->_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex), &Vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(UV), &UV, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	std::string CubePath[6] = {
		"./textures/right.jpg",
		"./textures/left.jpg",
		"./textures/top.jpg",
		"./textures/bottom.jpg",
		"./textures/front.jpg",
		"./textures/back.jpg"
	};

	glGenTextures(1, &this->_CubemapTexture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->_CubemapTexture);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	for (int i = 0; i < 6; i++) {
		int	ImgWidth, ImgHeight, ImgChannel;
		unsigned char	*bytes = stbi_load(CubePath[i].c_str(), &ImgWidth, &ImgHeight, &ImgChannel, 0);
		if(bytes) {
			stbi_set_flip_vertically_on_load(false);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, ImgWidth, ImgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
		}
		else {
			std::cout << "failed to load skybox :" << CubePath[i] << std::endl;
		}
		stbi_image_free(bytes);
	}

}

Skybox::~Skybox(void) {}

unsigned int	Skybox::GiveVAO() {
	return (this->_VAO);
}

unsigned int	Skybox::GiveCubemapTexture() {
	return (this->_CubemapTexture);
}