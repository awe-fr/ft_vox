#pragma once

#include <View/ViewVars.hpp>
#include <Model/BlockMapChunk.hpp>
#include <vector>

class	ViewChunk {
	private:
		std::vector<glm::vec2>	_TextureBuffer;
		std::vector<glm::vec3>	_VertexBuffer;
		GLuint 					_GlTextureBuffer;
		GLuint					_GlVertexBuffer;
		GLuint					_VAO;
        const int               _coord[2];

		void					VertexRight(int x, int y, int z, const std::array<float, 4> array);
		void					VertexFront(int x, int y, int z, const std::array<float, 4> array);
		void					VertexDown(int x, int y, int z, const std::array<float, 4> array);
		void					VertexBack(int x, int y, int z, const std::array<float, 4> array);
		void					VertexLeft(int x, int y, int z, const std::array<float, 4> array);
		void					VertexUp(int x, int y, int z, const std::array<float, 4> array);

	public:
        ViewChunk(BlockMapChunk *block_chunk);
        ~ViewChunk(void);

		std::vector<glm::vec2>	GiveTextureBuffer();
		std::vector<glm::vec3>	GiveVertexBuffer();
		GLuint					GiveGlTextureBuffer();
		GLuint					GiveGlVertexBuffer();
		int						GiveTextureBufferSize();
		int						GiveVertexBufferSize();
		GLuint					GiveVAO(void);
};