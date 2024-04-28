#include "../headers/Chunk.hpp"

void	Chunk::fill() {
	for (int y = 0; y < 16; y++) {
		for (int x = 0; x < 16; x++) {
			for (int z = 0; z < 256; z++) {
				if (z % 2 == 0 && x % 2 == 0 && y % 2 == 0)
					this->_Map[y][x][z] = 5;
				else
					this->_Map[y][x][z] = 0;
			}
		}
	}
}

void	Chunk::init() {
	glGenVertexArrays(1, &this->_VAO);
	glBindVertexArray(this->_VAO);

	glGenBuffers(1, &this->_GlVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->_GlVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, this->_VertexBuffer.size() * sizeof(glm::vec3), &this->_VertexBuffer[0], GL_DYNAMIC_DRAW);

	glGenBuffers(1, &this->_GlTextureBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->_GlTextureBuffer);
	glBufferData(GL_ARRAY_BUFFER, this->_TextureBuffer.size() * sizeof(glm::vec2), &this->_TextureBuffer[0], GL_DYNAMIC_DRAW);
}

void	Chunk::which_can_see() {
	int y = 0;
	int x = 0;
	int z = 0;
	while (y < 16) {
		while (x < 16) {
			while (z < 256) {
				if (this->_Map[y][x][z] != 0) {
					if (z == 255)
						VertexUp(x, y, z);
					else if (this->_Map[y][x][z + 1] == 0)
						VertexUp(x, y, z);
					if (z == 0)
						VertexDown(x, y, z);
					else if (this->_Map[y][x][z - 1] == 0)
						VertexDown(x, y, z);
					if (x == 15)
						VertexLeft(x, y, z);
					else if (this->_Map[y][x + 1][z] == 0)
						VertexLeft(x, y, z);
					if (x == 0)
						VertexRight(x, y, z);
					else if (this->_Map[y][x - 1][z] == 0)
						VertexRight(x, y, z);
					if (y == 15)
						VertexFront(x, y, z);
					else if (this->_Map[y + 1][x][z] == 0)
						VertexFront(x, y, z);
					if (y == 0)
						VertexBack(x, y, z);
					else if (this->_Map[y - 1][x][z] == 0)
						VertexBack(x, y, z);
				}
				z++;
			}
			z = 0;
			x++;
		}
		x = 0;
		y++;
 	}
}

void	Chunk::TextureAssignId(int id, float *a, float *b, float *c, float *d) {
	switch(id) {
		case 1:
			*a =  1;
			*b =  0.75;
			*c =  0;
			*d =  0.25;
			break;
		case 2:
			*a =  1;
			*b =  0.75;
			*c =  0.25;
			*d =  0.50;
			break;
		case 3:
			*a =  1;
			*b =  0.75;
			*c =  0.75;
			*d =  1;
			break;
		case 4:
			*a =  0.75;
			*b =  0.50;
			*c =  0;
			*d =  0.25;
			break;
		case 5:
			*a =  0.75;
			*b =  0.50;
			*c =  0.25;
			*d =  0.50;
			break;
	}
}

void	Chunk::TextureAssignTopId(int id, float *a, float *b, float *c, float *d) {
	switch(id) {
		case 1:
			*a =  1;
			*b =  0.75;
			*c =  0;
			*d =  0.25;
			break;
		case 2:
			*a =  1;
			*b =  0.75;
			*c =  0.50;
			*d =  0.75;
			break;
		case 3:
			*a =  1;
			*b =  0.75;
			*c =  0.75;
			*d =  1;
			break;
		case 4:
			*a =  0.75;
			*b =  0.50;
			*c =  0;
			*d =  0.25;
			break;
		case 5:
			*a =  0.75;
			*b =  0.50;
			*c =  0.50;
			*d =  0.75;
			break;
	}
}

void	Chunk::TextureAssignBotId(int id, float *a, float *b, float *c, float *d) {
	switch(id) {
		case 1:
			*a =  1;
			*b =  0.75;
			*c =  0;
			*d =  0.25;
			break;
		case 2:
			*a =  1;
			*b =  0.75;
			*c =  0;
			*d =  0.25;
			break;
		case 3:
			*a =  1;
			*b =  0.75;
			*c =  0.75;
			*d =  1;
			break;
		case 4:
			*a =  0.75;
			*b =  0.50;
			*c =  0;
			*d =  0.25;
			break;
		case 5:
			*a =  1;
			*b =  0.75;
			*c =  0;
			*d =  0.25;
			break;
	}
}

void	Chunk::VertexUp(int x, int y, int z) {
	float a, b, c, d;
	TextureAssignTopId(this->_Map[y][x][z], &a, &b, &c, &d);
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0001f, (z * 1) + 1.0f, (y * 1) + 1.0001f));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0001f, (z * 1) + 1.0f, (y * 1) + (-0.0001f)));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + (-0.0001f), (z * 1) + 1.0f, (y * 1) + (-0.0001f)));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0001f, (z * 1) + 1.0f, (y * 1) + 1.0001f));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + (-0.0001f), (z * 1) + 1.0f, (y * 1) + (-0.0001f)));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + (-0.0001f), (z * 1) + 1.0f, (y * 1) + 1.0001f));
	this->_TextureBuffer.push_back(glm::vec2(c, a));
	this->_TextureBuffer.push_back(glm::vec2(c, b));
	this->_TextureBuffer.push_back(glm::vec2(d, b));
	this->_TextureBuffer.push_back(glm::vec2(c, a));
	this->_TextureBuffer.push_back(glm::vec2(d, b));
	this->_TextureBuffer.push_back(glm::vec2(d, a));
}

void	Chunk::VertexDown(int x, int y, int z) {
	float a, b, c, d;
	TextureAssignBotId(this->_Map[y][x][z], &a, &b, &c, &d);
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0001f, (z * 1) + 0.0f, (y * 1) + 1.0001f));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + (-0.0001f), (z * 1) + 0.0f, (y * 1) + 1.0001f));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + (-0.0001f), (z * 1) + 0.0f, (y * 1) + (-0.0001f)));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0001f, (z * 1) + 0.0f, (y * 1) + 1.0001f));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + (-0.0001f), (z * 1) + 0.0f, (y * 1) + (-0.0001f)));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0001f, (z * 1) + 0.0f, (y * 1) + (-0.0001f)));
	this->_TextureBuffer.push_back(glm::vec2(c, b));
	this->_TextureBuffer.push_back(glm::vec2(d, b));
	this->_TextureBuffer.push_back(glm::vec2(d, a));
	this->_TextureBuffer.push_back(glm::vec2(c, b));
	this->_TextureBuffer.push_back(glm::vec2(d, a));
	this->_TextureBuffer.push_back(glm::vec2(c, a));
}

void	Chunk::VertexRight(int x, int y, int z) {
	float a, b, c, d;
	TextureAssignId(this->_Map[y][x][z], &a, &b, &c, &d);
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + (-0.0001f), (y * 1) + (-0.0001f)));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + (-0.0001f), (y * 1) + 1.0001f));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 1.0001f, (y * 1) + 1.0001f));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + (-0.0001f), (y * 1) + (-0.0001f)));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 1.0001f, (y * 1) + 1.0001f));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 1.0001f, (y * 1) + (-0.0001f)));
	this->_TextureBuffer.push_back(glm::vec2(c, b));
	this->_TextureBuffer.push_back(glm::vec2(d, b));
	this->_TextureBuffer.push_back(glm::vec2(d, a));
	this->_TextureBuffer.push_back(glm::vec2(c, b));
	this->_TextureBuffer.push_back(glm::vec2(d, a));
	this->_TextureBuffer.push_back(glm::vec2(c, a));
	
}

void	Chunk::VertexLeft(int x, int y, int z) {
	float a, b, c, d;
	TextureAssignId(this->_Map[y][x][z], &a, &b, &c, &d);
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + (-0.0001f), (y * 1) + (-0.0001f)));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 1.0001f, (y * 1) + (-0.0001f)));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 1.0001f, (y * 1) + 1.0001f));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + (-0.0001f), (y * 1) + (-0.0001f)));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 1.0001f, (y * 1) + 1.0001f));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + (-0.0001f), (y * 1) + 1.0001f));
	this->_TextureBuffer.push_back(glm::vec2(d, b));
	this->_TextureBuffer.push_back(glm::vec2(d, a));
	this->_TextureBuffer.push_back(glm::vec2(c, a));
	this->_TextureBuffer.push_back(glm::vec2(d, b));
	this->_TextureBuffer.push_back(glm::vec2(c, a));
	this->_TextureBuffer.push_back(glm::vec2(c, b));
}

void	Chunk::VertexBack(int x, int y, int z) {
	float a, b, c, d;
	TextureAssignId(this->_Map[y][x][z], &a, &b, &c, &d);
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.00001f, (z * 1) + 1.00001f, (y * 1) + 0.0f));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + (-0.0001f), (z * 1) + (-0.0001f), (y * 1) + 0.0f));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + (-0.0001f), (z * 1) + 1.00001f, (y * 1) + 0.0f));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.00001f, (z * 1) + 1.00001f, (y * 1) + 0.0f));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.00001f, (z * 1) + (-0.0001f), (y * 1) + 0.0f));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + (-0.0001f), (z * 1) + (-0.0001f), (y * 1) + 0.0f));
	this->_TextureBuffer.push_back(glm::vec2(c, a));
	this->_TextureBuffer.push_back(glm::vec2(d, b));
	this->_TextureBuffer.push_back(glm::vec2(d, a));
	this->_TextureBuffer.push_back(glm::vec2(c, a));
	this->_TextureBuffer.push_back(glm::vec2(c, b));
	this->_TextureBuffer.push_back(glm::vec2(d, b));
}

void	Chunk::VertexFront(int x, int y, int z) {
	float a, b, c, d;
	TextureAssignId(this->_Map[y][x][z], &a, &b, &c, &d);
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0001f, (z * 1) + 1.0001f, (y * 1) + 1.0f));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + (-0.0001f), (z * 1) + 1.0001f, (y * 1) + 1.0f));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0001f, (z * 1) + (-0.0001f), (y * 1) + 1.0f));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + (-0.0001f), (z * 1) + 1.0001f, (y * 1) + 1.0f));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + (-0.0001f), (z * 1) + (-0.0001f), (y * 1) + 1.0f));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0001f, (z * 1) + (-0.0001f), (y * 1) + 1.0f));
	this->_TextureBuffer.push_back(glm::vec2(d, a));
	this->_TextureBuffer.push_back(glm::vec2(c, a));
	this->_TextureBuffer.push_back(glm::vec2(d, b));
	this->_TextureBuffer.push_back(glm::vec2(c, a));
	this->_TextureBuffer.push_back(glm::vec2(c, b));
	this->_TextureBuffer.push_back(glm::vec2(d, b));
}

std::vector<glm::vec3>	Chunk::GiveVertexBuffer() {
	return (this->_VertexBuffer);
}

int	Chunk::GiveVertexBufferSize() {
	return (this->_VertexBuffer.size());
}

GLuint	Chunk::GiveGlVertexBuffer() {
	return (this->_GlVertexBuffer);
}

std::vector<glm::vec2>	Chunk::GiveTextureBuffer() {
	return (this->_TextureBuffer);
}

int	Chunk::GiveTextureBufferSize() {
	return (this->_TextureBuffer.size());
}

GLuint	Chunk::GiveGlTextureBuffer() {
	return (this->_GlTextureBuffer);
}