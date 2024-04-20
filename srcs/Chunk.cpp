#include "../headers/Chunk.hpp"

void	Chunk::fill() {
	for (int y = 0; y < 16; y++) {
		for (int x = 0; x < 16; x++) {
			for (int z = 0; z < 16; z++) {
				this->map[y][x][z] = 1;
			}
		}
	}
}

void	Chunk::init() {
	glGenBuffers(1, &this->vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->g_vertex_buffer_data), this->g_vertex_buffer_data, GL_DYNAMIC_DRAW);
}

void	Chunk::which_can_see() {
	static int j = 0;
	int y = 0;
	int x = 0;
	int z = 0;
	while (y < 16) {
		while (x < 16) {
			while (z < 16) {
				if (z == 15) {
					this->see.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 1.0f, (y * 1) + 1.0f));
					this->see.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 1.0f, (y * 1) + 0.0f));
					this->see.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 1.0f, (y * 1) + 0.0f));
					this->see.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 1.0f, (y * 1) + 1.0f));
					this->see.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 1.0f, (y * 1) + 0.0f));
					this->see.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 1.0f, (y * 1) + 1.0f));
					// j++;
				}
				// else if (this->map[y][x][z + 1] == 0) {
				// 	this->see.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 1.0f, (y * 1) + 1.0f));
				// 	this->see.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 1.0f, (y * 1) + 0.0f));
				// 	this->see.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 1.0f, (y * 1) + 0.0f));
				// 	this->see.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 1.0f, (y * 1) + 1.0f));
				// 	this->see.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 1.0f, (y * 1) + 0.0f));
				// 	this->see.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 1.0f, (y * 1) + 1.0f));
				// 	j++;
				// }
				z++;
				if (x == 15) {
					this->see.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 1.0f, (y * 1) + 1.0f));
					this->see.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 0.0f, (y * 1) + 0.0f));
					this->see.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 1.0f, (y * 1) + 0.0f));
					this->see.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 0.0f, (y * 1) + 0.0f));
					this->see.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 1.0f, (y * 1) + 1.0f));
					this->see.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 0.0f, (y * 1) + 1.0f));
					j++;
				}
				else if (x == 0) {
					this->see.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 0.0f, (y * 1) + 0.0f));
					this->see.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 0.0f, (y * 1) + 1.0f));
					this->see.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 1.0f, (y * 1) + 1.0f));
					this->see.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 0.0f, (y * 1) + 0.0f));
					this->see.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 1.0f, (y * 1) + 1.0f));
					this->see.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 1.0f, (y * 1) + 0.0f));
					j++;
				}
				// else if (this->map[y][x + 1][z] == 0) {
				// 	this->see.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 1.0f, (y * 1) + 1.0f));
				// 	this->see.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 0.0f, (y * 1) + 0.0f));
				// 	this->see.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 1.0f, (y * 1) + 0.0f));
				// 	this->see.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 0.0f, (y * 1) + 0.0f));
				// 	this->see.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 1.0f, (y * 1) + 1.0f));
				// 	this->see.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 0.0f, (y * 1) + 1.0f));
				// 	j++;
				// }
				// else if (this->map[y][x - 1][z] == 0) {
				// 	this->see.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 0.0f, (y * 1) + 0.0f));
				// 	this->see.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 0.0f, (y * 1) + 1.0f));
				// 	this->see.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 1.0f, (y * 1) + 1.0f));
				// 	this->see.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 0.0f, (y * 1) + 0.0f));
				// 	this->see.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 1.0f, (y * 1) + 1.0f));
				// 	this->see.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 1.0f, (y * 1) + 0.0f));
				// 	j++;
				// }
				if (y == 15) {
					this->see.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 1.0f, (y * 1) + 1.0f));
					this->see.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 1.0f, (y * 1) + 1.0f));
					this->see.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 0.0f, (y * 1) + 1.0f));
					this->see.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 1.0f, (y * 1) + 1.0f));
					this->see.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 0.0f, (y * 1) + 1.0f));
					this->see.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 0.0f, (y * 1) + 1.0f));
					j++;
				}
				else if (y == 0) {
					this->see.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 1.0f, (y * 1) + 0.0f));
					this->see.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 0.0f, (y * 1) + 0.0f));
					this->see.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 1.0f, (y * 1) + 0.0f));
					this->see.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 1.0f, (y * 1) + 0.0f));
					this->see.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 0.0f, (y * 1) + 0.0f));
					this->see.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 0.0f, (y * 1) + 0.0f));
					j++;
				}
				// else if (this->map[y + 1][x][z] == 0) {
				// 	this->see.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 1.0f, (y * 1) + 1.0f));
				// 	this->see.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 1.0f, (y * 1) + 1.0f));
				// 	this->see.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 0.0f, (y * 1) + 1.0f));
				// 	this->see.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 1.0f, (y * 1) + 1.0f));
				// 	this->see.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 0.0f, (y * 1) + 1.0f));
				// 	this->see.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 0.0f, (y * 1) + 1.0f));
				// 	j++;
				// }
				// else if (this->map[y - 1][x][z] == 0) {
				// 	this->see.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 1.0f, (y * 1) + 0.0f));
				// 	this->see.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 0.0f, (y * 1) + 0.0f));
				// 	this->see.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 1.0f, (y * 1) + 0.0f));
				// 	this->see.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 1.0f, (y * 1) + 0.0f));
				// 	this->see.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 0.0f, (y * 1) + 0.0f));
				// 	this->see.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 0.0f, (y * 1) + 0.0f));
				// 	j++;
				// }
			}
			z = 0;
			x++;
		}
		x = 0;
		y++;
 	}
	std::cout << j << std::endl;
}

std::vector<glm::vec3>	Chunk::GiveVertexBuffer() {
	return (this->see);
}

// void	Chunk::FillBuffer() {
// 	this->g_vertex_buffer_data = new GLfloat[this->see.size() * 3];
// 	for (size_t i = 0; i < this->see.size(); ++i) {
// 		this->g_vertex_buffer_data[i * 3] = this->see[i].x;
// 		this->g_vertex_buffer_data[i * 3 + 1] = this->see[i].y;
// 		this->g_vertex_buffer_data[i * 3 + 2] = this->see[i].z;
// 	}
// }

int	Chunk::GiveVertexBufferSize() {
	return (this->see.size());
}