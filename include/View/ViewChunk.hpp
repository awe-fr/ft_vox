#pragma once

#include <View/ViewVars.hpp>
#include <Model/BlockMapChunk.hpp>
#include <vector>

class	ViewChunk {
	private:
		std::vector<glm::vec2>	_TextureBuffer;
		std::vector<glm::vec3>	_VertexBuffer;
		std::vector<glm::vec2>	_TextureBufferWaheur;
		std::vector<glm::vec3>	_VertexBufferWaheur;
		glm::mat4				_model;
		GLuint 					_GlTextureBuffer;
		GLuint					_GlVertexBuffer;
		GLuint					_VAO;
		GLuint 					_GlTextureBufferWaheur;
		GLuint					_GlVertexBufferWaheur;
		GLuint					_VAOWaheur;
        const int               _coord[2];
		bool					_binded;

		void					VertexRight(int x, int y, int z, const std::array<float, 4> array);
		void					VertexFront(int x, int y, int z, const std::array<float, 4> array);
		void					VertexDown(int x, int y, int z, const std::array<float, 4> array);
		void					VertexBack(int x, int y, int z, const std::array<float, 4> array);
		void					VertexLeft(int x, int y, int z, const std::array<float, 4> array);
		void					VertexUp(int x, int y, int z, const std::array<float, 4> array);
		void					WaheurAssignment(int x, int y, int z, const std::array<float, 4> array);

	public:
        ViewChunk(BlockMapChunk *block_chunk);
        ~ViewChunk(void);

		glm::mat4				GiveModel();
		GLuint					GiveGlTextureBuffer();
		GLuint					GiveGlTextureBufferWaheur();
		GLuint					GiveGlVertexBuffer();
		GLuint					GiveGlVertexBufferWaheur();
		int						GiveVertexBufferSizeWaheur();
		int						GiveTextureBufferSize();
		int						GiveVertexBufferSize();
		void					bindBuffer();
		GLuint					GiveVAO();
		GLuint					GiveVAOWaheur();
		bool					IsBinded();
};