#pragma once

#include "Major.h"

class	Chunk {
	private:
		std::vector<glm::vec2>	_TextureBuffer;
		std::vector<glm::vec3>	_VertexBuffer;
		GLuint 					_GlTextureBuffer;
		GLuint					_GlVertexBuffer;
		GLuint					_VAO;
		int						_Map[16][16][256];
	public:
		std::vector<glm::vec2>	GiveTextureBuffer();
		std::vector<glm::vec3>	GiveVertexBuffer();
		GLuint					GiveGlTextureBuffer();
		GLuint					GiveGlVertexBuffer();
		void					which_can_see();
		void					init();
		void					fill();
		int						GiveTextureBufferSize();
		int						GiveVertexBufferSize();
};