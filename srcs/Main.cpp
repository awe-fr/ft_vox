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

	Skybox		Sky;
	Sky.init();

	GLuint	ProgramID = LoadShaders("./shaders/shader.vert", "./shaders/shader.frag");
	GLuint	SkyboxID = LoadShaders("./shaders/skybox.vert", "./shaders/skybox.frag");
	
	GLuint textu = loadpng("./textures/blocks.png");

	glUseProgram(ProgramID);
	GLuint tex0Uni = glGetUniformLocation(ProgramID, "tex");
	glUniform1i(tex0Uni, 0);

	GLuint ProjectionID = glGetUniformLocation(ProgramID, "Projection");
	GLuint ViewID = glGetUniformLocation(ProgramID, "View");
	GLuint ModelID = glGetUniformLocation(ProgramID, "Model");

	glUseProgram(SkyboxID);
	GLuint tex0Sky = glGetUniformLocation(SkyboxID, "skybox");
	glUniform1i(tex0Sky, 0);
	// Sky.init();


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
		// std::cout << 1 / DeltaTime << std::endl;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(ProgramID);
		glBindVertexArray(Map.GiveVAO());

		glEnable(GL_CULL_FACE);
		glm::mat4 Model = glm::mat4(1.0f);
		glBindTexture(GL_TEXTURE_2D, textu);

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


		glDepthFunc(GL_LEQUAL);
		glDisable(GL_CULL_FACE);
		glUseProgram(SkyboxID);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		view = glm::mat4(glm::mat3(glm::lookAt(-Player.GivePosition(), (-Player.GivePosition() + Player.GiveDirection()), -Player.GiveUp())));
		projection = glm::perspective(Player.GiveFOV(), (float) WIDTH / (float)HEIGHT, 0.1f, 1010.0f);
		glUniformMatrix4fv(glGetUniformLocation(SkyboxID, "view"), 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(SkyboxID, "projection"), 1, GL_FALSE, &projection[0][0]);

		glBindVertexArray(Sky.GiveVAO());
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, Sky.GiveCubemapTexture());
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);



		glDepthFunc(GL_LESS);

		Player.Movements(App.GiveWindow());
		/*temp*/
	}
}

void DestroyTextures() {
	//don't forget to implement it
	//glDeleteTextures(1, &texture);
}