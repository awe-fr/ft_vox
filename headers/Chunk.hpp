#pragma once

#include "Major.h"

class	Chunk {
	private:
		int map[16][16][256];
		GLfloat	*g_vertex_buffer_data;
		GLuint vertexbuffer;
		std::vector<glm::vec3> see;
	public:
		void	init();
		void	which_can_see();
		void	fill();
		std::vector<glm::vec3> GiveVertexBuffer();
		int	GiveVertexBufferSize();
		// void	FillBuffer();
};