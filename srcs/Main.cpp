#include "../headers/Major.h"

float	DeltaTime;

void getDeltaTime() {
	static double last = glfwGetTime();

	double now = glfwGetTime();
	DeltaTime = (float)(now - last);
	last = now;
}

int	main() {
	Chunk		Map;
	WindowApp	App;
	PlayerInfo	Player;
	if (App.InitWindow() == true)
		exit(1);
	Player.InitPlayer();

	/*temp*/
	Map.fill();
	Map.which_can_see();
	Map.init();

	// std::vector<glm::vec3> UV = Map.GiveVertexBuffer();
	// GLfloat g_uv_buffer_data[UV.size() * 2];
	// unsigned long int b = 0;
	// while (b < UV.size() * 2) {
	// 	g_uv_buffer_data[b] = 0;
	// 	g_uv_buffer_data[b + 1] = 0;
	// 	g_uv_buffer_data[b + 2] = 0;
	// 	g_uv_buffer_data[b + 3] = 1;
	// 	g_uv_buffer_data[b + 4] = 1;
	// 	g_uv_buffer_data[b + 5] = 1;
	// 	b += 6;
	// }

	GLuint	ProgramID = LoadShaders("./shaders/shader.vert", "./shaders/shader.frag");
	
	GLuint textu = loadpng("./textures/dirt.png");


	GLuint tex0Uni = glGetUniformLocation(ProgramID, "tex");
	glUniform1i(tex0Uni, 0);

	GLuint ProjectionID = glGetUniformLocation(ProgramID, "Projection");
	GLuint ViewID = glGetUniformLocation(ProgramID, "View");
	GLuint ModelID = glGetUniformLocation(ProgramID, "Model");

	glClearColor(0.6f, 0.0f, 0.8f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	/*temp*/
	glBindTexture(GL_TEXTURE_2D, textu);
	while(App.IsClosed() == false) {
		/*temp*/
		getDeltaTime();
		std::cout << 1 / DeltaTime << std::endl;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(ProgramID);

		glm::mat4 Model = glm::mat4(1.0f);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, Map.GiveGlTextureBuffer());
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);

		glUniformMatrix4fv(ProjectionID, 1, GL_FALSE, &Player.GiveProjection()[0][0]);
		glUniformMatrix4fv(ViewID, 1, GL_FALSE, &Player.GiveView()[0][0]);
		glUniformMatrix4fv(ModelID, 1, GL_FALSE, &Model[0][0]);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, Map.GiveGlVertexBuffer());
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
		glDrawArrays(GL_TRIANGLES, 0, Map.GiveVertexBufferSize());
		// glDrawArrays(GL_TRIANGLES, 0, 3 * 12);
		glDisableVertexAttribArray(0);

		Player.Movements(App.GiveWindow());
		/*temp*/
	}
}

void DestroyTextures() {
	//don't forget to implement it
	//glDeleteTextures(1, &texture);
}