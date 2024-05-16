#pragma once

#include <View/ViewVars.hpp>
#include <Model/BlockMapChunk.hpp>
#include <vector>

class	ViewChunk {
	private:
		std::vector<glm::vec3>	_VertexBufferNormal;
		GLuint					_GlVertexBufferNormal;

		std::vector<glm::vec2>	_TextureBuffer;
		std::vector<glm::vec3>	_VertexBuffer;
		GLuint 					_GlTextureBuffer;
		GLuint					_GlVertexBuffer;
		GLuint					_VAO;

		std::vector<glm::vec2>	_TextureBufferWaheur;
		std::vector<glm::vec3>	_VertexBufferWaheur;
		GLuint 					_GlTextureBufferWaheur;
		GLuint					_GlVertexBufferWaheur;
		GLuint					_VAOWaheur;

		glm::mat4				_model;
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


		GLuint					GiveGlVertexBufferNormal();
		GLuint					GiveGlTextureBuffer();
		GLuint					GiveGlVertexBuffer();
		GLuint					GiveVAO();
		int						GiveTextureBufferSize();
		int						GiveVertexBufferSize();
		
		GLuint					GiveGlTextureBufferWaheur();
		GLuint					GiveGlVertexBufferWaheur();
		GLuint					GiveVAOWaheur();
		int						GiveVertexBufferSizeWaheur();
		
		glm::mat4				GiveModel();
		void					bindBuffer();
		bool					IsBinded();
};