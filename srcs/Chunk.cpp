#include "../headers/Chunk.hpp"

void	Chunk::fill() {
	for (int y = 0; y < 16; y++) {
		for (int x = 0; x < 16; x++) {
			for (int z = 0; z < 256; z++) {
				if (z % 2 == 0 && x % 2 == 0 && y % 2 == 0)
					this->_Map[y][x][z] = 1;
				else
					this->_Map[y][x][z] = 0;
			}
		}
	}
	this->_Map[8][8][254] = 0;
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
					if (z == 255) {
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 1.0f, (y * 1) + 1.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 1.0f, (y * 1) + 0.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 1.0f, (y * 1) + 0.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 1.0f, (y * 1) + 1.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 1.0f, (y * 1) + 0.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 1.0f, (y * 1) + 1.0f));
						this->_TextureBuffer.push_back(glm::vec2(0, 1));
						this->_TextureBuffer.push_back(glm::vec2(0, 0));
						this->_TextureBuffer.push_back(glm::vec2(1, 0));
						this->_TextureBuffer.push_back(glm::vec2(0, 1));
						this->_TextureBuffer.push_back(glm::vec2(1, 0));
						this->_TextureBuffer.push_back(glm::vec2(1, 1));
					}
					else if (this->_Map[y][x][z + 1] == 0) {
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 1.0f, (y * 1) + 1.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 1.0f, (y * 1) + 0.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 1.0f, (y * 1) + 0.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 1.0f, (y * 1) + 1.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 1.0f, (y * 1) + 0.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 1.0f, (y * 1) + 1.0f));
						this->_TextureBuffer.push_back(glm::vec2(0, 1));
						this->_TextureBuffer.push_back(glm::vec2(0, 0));
						this->_TextureBuffer.push_back(glm::vec2(1, 0));
						this->_TextureBuffer.push_back(glm::vec2(0, 1));
						this->_TextureBuffer.push_back(glm::vec2(1, 0));
						this->_TextureBuffer.push_back(glm::vec2(1, 1));
					}
					if (z == 0) {
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 0.0f, (y * 1) + 1.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 0.0f, (y * 1) + 1.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 0.0f, (y * 1) + 0.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 0.0f, (y * 1) + 1.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 0.0f, (y * 1) + 0.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 0.0f, (y * 1) + 0.0f));
						this->_TextureBuffer.push_back(glm::vec2(0, 0));
						this->_TextureBuffer.push_back(glm::vec2(1, 0));
						this->_TextureBuffer.push_back(glm::vec2(1, 1));
						this->_TextureBuffer.push_back(glm::vec2(0, 0));
						this->_TextureBuffer.push_back(glm::vec2(1, 1));
						this->_TextureBuffer.push_back(glm::vec2(0, 1));
					}
					else if (this->_Map[y][x][z - 1] == 0) {
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 0.0f, (y * 1) + 1.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 0.0f, (y * 1) + 1.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 0.0f, (y * 1) + 0.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 0.0f, (y * 1) + 1.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 0.0f, (y * 1) + 0.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 0.0f, (y * 1) + 0.0f));
						this->_TextureBuffer.push_back(glm::vec2(0, 0));
						this->_TextureBuffer.push_back(glm::vec2(1, 0));
						this->_TextureBuffer.push_back(glm::vec2(1, 1));
						this->_TextureBuffer.push_back(glm::vec2(0, 0));
						this->_TextureBuffer.push_back(glm::vec2(1, 1));
						this->_TextureBuffer.push_back(glm::vec2(0, 1));
					}
					if (x == 15) {
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 0.0f, (y * 1) + 0.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 1.0f, (y * 1) + 0.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 1.0f, (y * 1) + 1.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 0.0f, (y * 1) + 0.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 1.0f, (y * 1) + 1.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 0.0f, (y * 1) + 1.0f));
						this->_TextureBuffer.push_back(glm::vec2(1, 0));
						this->_TextureBuffer.push_back(glm::vec2(1, 1));
						this->_TextureBuffer.push_back(glm::vec2(0, 1));
						this->_TextureBuffer.push_back(glm::vec2(1, 0));
						this->_TextureBuffer.push_back(glm::vec2(0, 1));
						this->_TextureBuffer.push_back(glm::vec2(0, 0));
					}
					else if (this->_Map[y][x + 1][z] == 0) {
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 0.0f, (y * 1) + 0.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 1.0f, (y * 1) + 0.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 1.0f, (y * 1) + 1.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 0.0f, (y * 1) + 0.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 1.0f, (y * 1) + 1.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 0.0f, (y * 1) + 1.0f));
						this->_TextureBuffer.push_back(glm::vec2(1, 0));
						this->_TextureBuffer.push_back(glm::vec2(1, 1));
						this->_TextureBuffer.push_back(glm::vec2(0, 1));
						this->_TextureBuffer.push_back(glm::vec2(1, 0));
						this->_TextureBuffer.push_back(glm::vec2(0, 1));
						this->_TextureBuffer.push_back(glm::vec2(0, 0));
					}
					if (x == 0) {
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 0.0f, (y * 1) + 0.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 0.0f, (y * 1) + 1.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 1.0f, (y * 1) + 1.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 0.0f, (y * 1) + 0.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 1.0f, (y * 1) + 1.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 1.0f, (y * 1) + 0.0f));
						this->_TextureBuffer.push_back(glm::vec2(0, 0));
						this->_TextureBuffer.push_back(glm::vec2(1, 0));
						this->_TextureBuffer.push_back(glm::vec2(1, 1));
						this->_TextureBuffer.push_back(glm::vec2(0, 0));
						this->_TextureBuffer.push_back(glm::vec2(1, 1));
						this->_TextureBuffer.push_back(glm::vec2(0, 1));
					}
					else if (this->_Map[y][x - 1][z] == 0) {
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 0.0f, (y * 1) + 0.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 0.0f, (y * 1) + 1.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 1.0f, (y * 1) + 1.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 0.0f, (y * 1) + 0.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 1.0f, (y * 1) + 1.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 1.0f, (y * 1) + 0.0f));
						this->_TextureBuffer.push_back(glm::vec2(0, 0));
						this->_TextureBuffer.push_back(glm::vec2(1, 0));
						this->_TextureBuffer.push_back(glm::vec2(1, 1));
						this->_TextureBuffer.push_back(glm::vec2(0, 0));
						this->_TextureBuffer.push_back(glm::vec2(1, 1));
						this->_TextureBuffer.push_back(glm::vec2(0, 1));
					}
					if (y == 15) {
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 1.0f, (y * 1) + 1.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 1.0f, (y * 1) + 1.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 0.0f, (y * 1) + 1.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 1.0f, (y * 1) + 1.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 0.0f, (y * 1) + 1.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 0.0f, (y * 1) + 1.0f));
						this->_TextureBuffer.push_back(glm::vec2(1, 1));
						this->_TextureBuffer.push_back(glm::vec2(0, 1));
						this->_TextureBuffer.push_back(glm::vec2(1, 0));
						this->_TextureBuffer.push_back(glm::vec2(0, 1));
						this->_TextureBuffer.push_back(glm::vec2(0, 0));
						this->_TextureBuffer.push_back(glm::vec2(1, 0));
					}
					else if (this->_Map[y + 1][x][z] == 0) {
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 1.0f, (y * 1) + 1.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 1.0f, (y * 1) + 1.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 0.0f, (y * 1) + 1.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 1.0f, (y * 1) + 1.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 0.0f, (y * 1) + 1.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 0.0f, (y * 1) + 1.0f));
						this->_TextureBuffer.push_back(glm::vec2(1, 1));
						this->_TextureBuffer.push_back(glm::vec2(0, 1));
						this->_TextureBuffer.push_back(glm::vec2(1, 0));
						this->_TextureBuffer.push_back(glm::vec2(0, 1));
						this->_TextureBuffer.push_back(glm::vec2(0, 0));
						this->_TextureBuffer.push_back(glm::vec2(1, 0));
					}
					if (y == 0) {
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 1.0f, (y * 1) + 0.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 0.0f, (y * 1) + 0.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 1.0f, (y * 1) + 0.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 1.0f, (y * 1) + 0.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 0.0f, (y * 1) + 0.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 0.0f, (y * 1) + 0.0f));
						this->_TextureBuffer.push_back(glm::vec2(0, 1));
						this->_TextureBuffer.push_back(glm::vec2(1, 0));
						this->_TextureBuffer.push_back(glm::vec2(1, 1));
						this->_TextureBuffer.push_back(glm::vec2(0, 1));
						this->_TextureBuffer.push_back(glm::vec2(0, 0));
						this->_TextureBuffer.push_back(glm::vec2(1, 0));
					}
					else if (this->_Map[y - 1][x][z] == 0) {
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 1.0f, (y * 1) + 0.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 0.0f, (y * 1) + 0.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 1.0f, (y * 1) + 0.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 1.0f, (y * 1) + 0.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 0.0f, (y * 1) + 0.0f));
						this->_VertexBuffer.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 0.0f, (y * 1) + 0.0f));
						this->_TextureBuffer.push_back(glm::vec2(0, 1));
						this->_TextureBuffer.push_back(glm::vec2(1, 0));
						this->_TextureBuffer.push_back(glm::vec2(1, 1));
						this->_TextureBuffer.push_back(glm::vec2(0, 1));
						this->_TextureBuffer.push_back(glm::vec2(0, 0));
						this->_TextureBuffer.push_back(glm::vec2(1, 0));
					}
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