#include <View/ViewChunk.hpp>

ViewChunk::ViewChunk(BlockMapChunk *block_chunk) : _coord{block_chunk->getCoordX(), block_chunk->getCoordY()}
{
    for (size_t i = 0; i < CHUNK_SIZE; i++)
    {
        for (size_t j = 0; j < CHUNK_SIZE; j++)
        {
            for (size_t k = 0; k < CHUNK_HEIGHT; k++)
            {
                Block block = block_chunk->getBlock(j, i, k);
                if (block.getName() == "void")
                    continue;
                if (k == CHUNK_HEIGHT - 1 || block_chunk->getBlock(j, i, k + 1).getName() == "void")
                    this->VertexUp(j, i, k, block.getTextureTop());
                if (k == 0 || block_chunk->getBlock(j, i, k - 1).getName() == "void")
                    this->VertexDown(j, i, k, block.getTextureBottom());
                if (j == CHUNK_SIZE - 1 || block_chunk->getBlock(j + 1, i, k).getName() == "void")
                    this->VertexLeft(j, i, k, block.getTextureSide());
                if (j == 0 || block_chunk->getBlock(j - 1, i, k).getName() == "void")
                    this->VertexRight(j, i, k, block.getTextureSide());
                if (i == CHUNK_SIZE - 1 || block_chunk->getBlock(j, i + 1, k).getName() == "void")
                    this->VertexFront(j, i, k, block.getTextureSide());
                if (i == 0 || block_chunk->getBlock(j, i - 1, k).getName() == "void")
                    this->VertexBack(j, i, k, block.getTextureSide());
            }
        }
    }

    glGenVertexArrays(1, &this->_VAO);
	glBindVertexArray(this->_VAO);

	glGenBuffers(1, &this->_GlVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->_GlVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, this->_VertexBuffer.size() * sizeof(glm::vec3), &this->_VertexBuffer[0], GL_DYNAMIC_DRAW);

	glGenBuffers(1, &this->_GlTextureBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->_GlTextureBuffer);
	glBufferData(GL_ARRAY_BUFFER, this->_TextureBuffer.size() * sizeof(glm::vec2), &this->_TextureBuffer[0], GL_DYNAMIC_DRAW);
}

ViewChunk::~ViewChunk(void) {}

void	ViewChunk::VertexUp(int x, int y, int z, const std::array<float, 4> array) {
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0001f, (z * 1) + 1.0f, (y * 1) + 1.0001f));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0001f, (z * 1) + 1.0f, (y * 1) + (-0.0001f)));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + (-0.0001f), (z * 1) + 1.0f, (y * 1) + (-0.0001f)));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0001f, (z * 1) + 1.0f, (y * 1) + 1.0001f));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + (-0.0001f), (z * 1) + 1.0f, (y * 1) + (-0.0001f)));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + (-0.0001f), (z * 1) + 1.0f, (y * 1) + 1.0001f));
	this->_TextureBuffer.push_back(glm::vec2(array[2], array[0]));
	this->_TextureBuffer.push_back(glm::vec2(array[2], array[1]));
	this->_TextureBuffer.push_back(glm::vec2(array[3], array[1]));
	this->_TextureBuffer.push_back(glm::vec2(array[2], array[0]));
	this->_TextureBuffer.push_back(glm::vec2(array[3], array[1]));
	this->_TextureBuffer.push_back(glm::vec2(array[3], array[0]));
}

void	ViewChunk::VertexDown(int x, int y, int z, const std::array<float, 4> array) {
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0001f, (z * 1) + 0.0f, (y * 1) + 1.0001f));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + (-0.0001f), (z * 1) + 0.0f, (y * 1) + 1.0001f));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + (-0.0001f), (z * 1) + 0.0f, (y * 1) + (-0.0001f)));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0001f, (z * 1) + 0.0f, (y * 1) + 1.0001f));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + (-0.0001f), (z * 1) + 0.0f, (y * 1) + (-0.0001f)));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0001f, (z * 1) + 0.0f, (y * 1) + (-0.0001f)));
	this->_TextureBuffer.push_back(glm::vec2(array[2], array[1]));
	this->_TextureBuffer.push_back(glm::vec2(array[3], array[1]));
	this->_TextureBuffer.push_back(glm::vec2(array[3], array[0]));
	this->_TextureBuffer.push_back(glm::vec2(array[2], array[1]));
	this->_TextureBuffer.push_back(glm::vec2(array[3], array[0]));
	this->_TextureBuffer.push_back(glm::vec2(array[2], array[0]));
}

void	ViewChunk::VertexRight(int x, int y, int z, const std::array<float, 4> array) {
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + (-0.0001f), (y * 1) + (-0.0001f)));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + (-0.0001f), (y * 1) + 1.0001f));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 1.0001f, (y * 1) + 1.0001f));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + (-0.0001f), (y * 1) + (-0.0001f)));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 1.0001f, (y * 1) + 1.0001f));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + 0.0f, (z * 1) + 1.0001f, (y * 1) + (-0.0001f)));
	this->_TextureBuffer.push_back(glm::vec2(array[2], array[1]));
	this->_TextureBuffer.push_back(glm::vec2(array[3], array[1]));
	this->_TextureBuffer.push_back(glm::vec2(array[3], array[0]));
	this->_TextureBuffer.push_back(glm::vec2(array[2], array[1]));
	this->_TextureBuffer.push_back(glm::vec2(array[3], array[0]));
	this->_TextureBuffer.push_back(glm::vec2(array[2], array[0]));
	
}

void	ViewChunk::VertexLeft(int x, int y, int z, const std::array<float, 4> array) {
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + (-0.0001f), (y * 1) + (-0.0001f)));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 1.0001f, (y * 1) + (-0.0001f)));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 1.0001f, (y * 1) + 1.0001f));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + (-0.0001f), (y * 1) + (-0.0001f)));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + 1.0001f, (y * 1) + 1.0001f));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0f, (z * 1) + (-0.0001f), (y * 1) + 1.0001f));
	this->_TextureBuffer.push_back(glm::vec2(array[3], array[1]));
	this->_TextureBuffer.push_back(glm::vec2(array[3], array[0]));
	this->_TextureBuffer.push_back(glm::vec2(array[2], array[0]));
	this->_TextureBuffer.push_back(glm::vec2(array[3], array[1]));
	this->_TextureBuffer.push_back(glm::vec2(array[2], array[0]));
	this->_TextureBuffer.push_back(glm::vec2(array[2], array[1]));
}

void	ViewChunk::VertexBack(int x, int y, int z, const std::array<float, 4> array) {
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.00001f, (z * 1) + 1.00001f, (y * 1) + 0.0f));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + (-0.0001f), (z * 1) + (-0.0001f), (y * 1) + 0.0f));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + (-0.0001f), (z * 1) + 1.00001f, (y * 1) + 0.0f));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.00001f, (z * 1) + 1.00001f, (y * 1) + 0.0f));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.00001f, (z * 1) + (-0.0001f), (y * 1) + 0.0f));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + (-0.0001f), (z * 1) + (-0.0001f), (y * 1) + 0.0f));
	this->_TextureBuffer.push_back(glm::vec2(array[2], array[0]));
	this->_TextureBuffer.push_back(glm::vec2(array[3], array[1]));
	this->_TextureBuffer.push_back(glm::vec2(array[3], array[0]));
	this->_TextureBuffer.push_back(glm::vec2(array[2], array[0]));
	this->_TextureBuffer.push_back(glm::vec2(array[2], array[1]));
	this->_TextureBuffer.push_back(glm::vec2(array[3], array[1]));
}

void	ViewChunk::VertexFront(int x, int y, int z, const std::array<float, 4> array) {
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0001f, (z * 1) + 1.0001f, (y * 1) + 1.0f));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + (-0.0001f), (z * 1) + 1.0001f, (y * 1) + 1.0f));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0001f, (z * 1) + (-0.0001f), (y * 1) + 1.0f));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + (-0.0001f), (z * 1) + 1.0001f, (y * 1) + 1.0f));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + (-0.0001f), (z * 1) + (-0.0001f), (y * 1) + 1.0f));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0001f, (z * 1) + (-0.0001f), (y * 1) + 1.0f));
	this->_TextureBuffer.push_back(glm::vec2(array[3], array[0]));
	this->_TextureBuffer.push_back(glm::vec2(array[2], array[0]));
	this->_TextureBuffer.push_back(glm::vec2(array[3], array[1]));
	this->_TextureBuffer.push_back(glm::vec2(array[2], array[0]));
	this->_TextureBuffer.push_back(glm::vec2(array[2], array[1]));
	this->_TextureBuffer.push_back(glm::vec2(array[3], array[1]));
}

std::vector<glm::vec3>	ViewChunk::GiveVertexBuffer() {
	return (this->_VertexBuffer);
}

int	ViewChunk::GiveVertexBufferSize() {
	return (this->_VertexBuffer.size());
}

GLuint	ViewChunk::GiveGlVertexBuffer() {
	return (this->_GlVertexBuffer);
}

std::vector<glm::vec2>	ViewChunk::GiveTextureBuffer() {
	return (this->_TextureBuffer);
}

int	ViewChunk::GiveTextureBufferSize() {
	return (this->_TextureBuffer.size());
}

GLuint	ViewChunk::GiveGlTextureBuffer() {
	return (this->_GlTextureBuffer);
}

GLuint ViewChunk::GiveVAO(void)
{
	return this->_VAO;
}