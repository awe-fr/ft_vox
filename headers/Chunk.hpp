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
		void					TextureAssignTopId(int id, float *a, float *b, float *c, float *d);
		void					TextureAssignBotId(int id, float *a, float *b, float *c, float *d);
		void					TextureAssignId(int id, float *a, float *b, float *c, float *d);
		void					VertexRight(int x, int y, int z);
		void					VertexFront(int x, int y, int z);
		void					VertexDown(int x, int y, int z);
		void					VertexBack(int x, int y, int z);
		void					VertexLeft(int x, int y, int z);
		void					VertexUp(int x, int y, int z);
		void					which_can_see();
		void					init();
		void					fill();
		int						GiveTextureBufferSize();
		int						GiveVertexBufferSize();
};