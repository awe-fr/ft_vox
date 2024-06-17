#include <View/ViewChunk.hpp>

ViewChunk::ViewChunk(BlockMapChunk *block_chunk) : _coord{block_chunk->getCoordX(), block_chunk->getCoordY()}
{
	this->_binded = false;
    for (size_t i = 0; i < CHUNK_SIZE; i++)
    {
        for (size_t j = 0; j < CHUNK_SIZE; j++)
        {
            for (size_t k = 0; k < CHUNK_HEIGHT; k++)
            {
                Block block = block_chunk->getBlock(j, i, k);
                if (block.getName() == "void")
                    continue;
				if (block.getName() == "waheur" && block_chunk->getBlock(j, i, k + 1).getName() == "void") {
					this->WaheurAssignment(j, i, k, block.getTextureTop());
					continue;
				}
				if (block.getName() == "waheur")
					continue;
                if (k == CHUNK_HEIGHT - 1 || block_chunk->getBlock(j, i, k + 1).getName() == "void" || block_chunk->getBlock(j, i, k + 1).getName() == "waheur")
                    this->VertexUp(j, i, k, block.getTextureTop());
                if (k == 0 || block_chunk->getBlock(j, i, k - 1).getName() == "void" || block_chunk->getBlock(j, i, k - 1).getName() == "waheur")
                    this->VertexDown(j, i, k, block.getTextureBottom());
                if (j == CHUNK_SIZE - 1 || block_chunk->getBlock(j + 1, i, k).getName() == "void" || block_chunk->getBlock(j + 1, i, k).getName() == "waheur")
                    this->VertexLeft(j, i, k, block.getTextureSide());
                if (j == 0 || block_chunk->getBlock(j - 1, i, k).getName() == "void" || block_chunk->getBlock(j - 1, i, k).getName() == "waheur")
                    this->VertexRight(j, i, k, block.getTextureSide());
                if (i == CHUNK_SIZE - 1 || block_chunk->getBlock(j, i + 1, k).getName() == "void" || block_chunk->getBlock(j, i + 1, k).getName() == "waheur")
                    this->VertexFront(j, i, k, block.getTextureSide());
                if (i == 0 || block_chunk->getBlock(j, i - 1, k).getName() == "void" || block_chunk->getBlock(j, i - 1, k).getName() == "waheur")
                    this->VertexBack(j, i, k, block.getTextureSide());
            }
        }
    }

	this->_model = glm::mat4(1);
	this->_model = glm::translate(this->_model, glm::vec3(this->_coord[0] * CHUNK_SIZE, 0, this->_coord[1] * CHUNK_SIZE));
}

void ViewChunk::bindBuffer() {
	glGenVertexArrays(1, &this->_VAO);
	glBindVertexArray(this->_VAO);

	glGenBuffers(1, &this->_GlVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->_GlVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, this->_VertexBuffer.size() * sizeof(glm::vec3), &this->_VertexBuffer[0], GL_STATIC_DRAW);

	glGenBuffers(1, &this->_GlTextureBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->_GlTextureBuffer);
	glBufferData(GL_ARRAY_BUFFER, this->_TextureBuffer.size() * sizeof(glm::vec2), &this->_TextureBuffer[0], GL_STATIC_DRAW);
	
	glGenBuffers(1, &this->_GlVertexBufferNormal);
	glBindBuffer(GL_ARRAY_BUFFER, this->_GlVertexBufferNormal);
	glBufferData(GL_ARRAY_BUFFER, this->_VertexBufferNormal.size() * sizeof(glm::vec3), &this->_VertexBufferNormal[0], GL_STATIC_DRAW);
	
	glGenVertexArrays(1, &this->_VAOWaheur);
	glBindVertexArray(this->_VAOWaheur);

	glGenBuffers(1, &this->_GlVertexBufferWaheur);
	glBindBuffer(GL_ARRAY_BUFFER, this->_GlVertexBufferWaheur);
	glBufferData(GL_ARRAY_BUFFER, this->_VertexBufferWaheur.size() * sizeof(glm::vec3), &this->_VertexBufferWaheur[0], GL_STATIC_DRAW);

	glGenBuffers(1, &this->_GlTextureBufferWaheur);
	glBindBuffer(GL_ARRAY_BUFFER, this->_GlTextureBufferWaheur);
	glBufferData(GL_ARRAY_BUFFER, this->_TextureBufferWaheur.size() * sizeof(glm::vec2), &this->_TextureBufferWaheur[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	this->_binded = true;

	this->_VertexSize = this->_VertexBuffer.size();
	this->_VertexSizeWaheur = this->_VertexBufferWaheur.size();

	this->_VertexBufferNormal.clear();
	this->_TextureBuffer.clear();
	this->_VertexBuffer.clear();
	this->_TextureBufferWaheur.clear();
	this->_VertexBufferWaheur.clear();
}

ViewChunk::~ViewChunk(void) {
	glDeleteBuffers(1, &this->_GlVertexBufferNormal);
	glDeleteBuffers(1, &this->_GlTextureBuffer);
	glDeleteBuffers(1, &this->_GlVertexBuffer);
	glDeleteVertexArrays(1 , &this->_VAO);

	glDeleteBuffers(1, &this->_GlTextureBufferWaheur);
	glDeleteBuffers(1, &this->_GlVertexBufferWaheur);
	glDeleteVertexArrays(1 , &this->_VAOWaheur);

}

bool ViewChunk::IsBinded() {
	return (this->_binded);
}

void ViewChunk::WaheurAssignment(int x, int y, int z, const std::array<float, 4> array) {
	this->_VertexBufferWaheur.push_back(glm::vec3((x * 1) + 1.0001f, (z * 1) + 0.93f, (y * 1) + 1.001f));
	this->_VertexBufferWaheur.push_back(glm::vec3((x * 1) + 1.0001f, (z * 1) + 0.93f, (y * 1) + (-0.0001f)));
	this->_VertexBufferWaheur.push_back(glm::vec3((x * 1) + (-0.0001f), (z * 1) + 0.93f, (y * 1) + (-0.0001f)));
	this->_VertexBufferWaheur.push_back(glm::vec3((x * 1) + 1.0001f, (z * 1) + 0.93f, (y * 1) + 1.0001f));
	this->_VertexBufferWaheur.push_back(glm::vec3((x * 1) + (-0.0001f), (z * 1) + 0.93f, (y * 1) + (-0.0001f)));
	this->_VertexBufferWaheur.push_back(glm::vec3((x * 1) + (-0.0001f), (z * 1) + 0.93f, (y * 1) + 1.0001f));
	this->_TextureBufferWaheur.push_back(glm::vec2(array[2], array[0]));
	this->_TextureBufferWaheur.push_back(glm::vec2(array[2], array[1]));
	this->_TextureBufferWaheur.push_back(glm::vec2(array[3], array[1]));
	this->_TextureBufferWaheur.push_back(glm::vec2(array[2], array[0]));
	this->_TextureBufferWaheur.push_back(glm::vec2(array[3], array[1]));
	this->_TextureBufferWaheur.push_back(glm::vec2(array[3], array[0]));
}

void	ViewChunk::VertexUp(int x, int y, int z, const std::array<float, 4> array) {
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0001f, (z * 1) + 1.0f, (y * 1) + 1.0001f));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0001f, (z * 1) + 1.0f, (y * 1) + (-0.0001f)));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + (-0.0001f), (z * 1) + 1.0f, (y * 1) + (-0.0001f)));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + 1.0001f, (z * 1) + 1.0f, (y * 1) + 1.0001f));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + (-0.0001f), (z * 1) + 1.0f, (y * 1) + (-0.0001f)));
	this->_VertexBuffer.push_back(glm::vec3((x * 1) + (-0.0001f), (z * 1) + 1.0f, (y * 1) + 1.0001f));

	for (int i = 0; i < 6; ++i) {
        this->_VertexBufferNormal.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
    }

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
	
	for (int i = 0; i < 6; ++i) {
        this->_VertexBufferNormal.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
    }
	
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

	for (int i = 0; i < 6; ++i) {
        this->_VertexBufferNormal.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
    }

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

	for (int i = 0; i < 6; ++i) {
        this->_VertexBufferNormal.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
    }

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

	for (int i = 0; i < 6; ++i) {
        this->_VertexBufferNormal.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
    }

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

	for (int i = 0; i < 6; ++i) {
        this->_VertexBufferNormal.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
    }

	this->_TextureBuffer.push_back(glm::vec2(array[3], array[0]));
	this->_TextureBuffer.push_back(glm::vec2(array[2], array[0]));
	this->_TextureBuffer.push_back(glm::vec2(array[3], array[1]));
	this->_TextureBuffer.push_back(glm::vec2(array[2], array[0]));
	this->_TextureBuffer.push_back(glm::vec2(array[2], array[1]));
	this->_TextureBuffer.push_back(glm::vec2(array[3], array[1]));
}

int	ViewChunk::GiveVertexBufferSize() {
	return (this->_VertexSize);
}

int	ViewChunk::GiveVertexBufferSizeWaheur() {
	return (this->_VertexSizeWaheur);
}

GLuint	ViewChunk::GiveGlVertexBuffer() {
	return (this->_GlVertexBuffer);
}

GLuint	ViewChunk::GiveGlVertexBufferWaheur() {
	return (this->_GlVertexBufferWaheur);
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

GLuint	ViewChunk::GiveGlTextureBufferWaheur() {
	return (this->_GlTextureBufferWaheur);
}

GLuint ViewChunk::GiveVAOWaheur(void)
{
	return this->_VAOWaheur;
}

glm::mat4 ViewChunk::GiveModel() {
	return (this->_model);
}

GLuint	ViewChunk::GiveGlVertexBufferNormal() {
	return (this->_GlVertexBufferNormal);
}