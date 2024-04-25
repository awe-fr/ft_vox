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

	GLuint colorbuffer;

	GLfloat g_color_buffer_data[Map.GiveVertexBufferSize() * 4];
	int i = 0;
	while (i < Map.GiveVertexBufferSize() * 4) {
		if (i  % 36 < 12) {
			g_color_buffer_data[i] = 0.1f;
			g_color_buffer_data[i + 1] = 0.1f;
			g_color_buffer_data[i + 2] = 0.1f;
			g_color_buffer_data[i + 3] = 1.0f;
		}
		else if (i % 36 < 24){
			g_color_buffer_data[i] = 0.2f;
			g_color_buffer_data[i + 1] = 0.2f;
			g_color_buffer_data[i + 2] = 0.2f;
			g_color_buffer_data[i + 3] = 1.0f;
		}
		else {
			g_color_buffer_data[i] = 0.3f;
			g_color_buffer_data[i + 1] = 0.3f;
			g_color_buffer_data[i + 2] = 0.3f;
			g_color_buffer_data[i + 3] = 1.0f;
		}
		i += 4;
	}
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);



	GLuint	ProgramID = LoadShaders("./shaders/shader.vert", "./shaders/shader.frag");
	
	GLuint ProjectionID = glGetUniformLocation(ProgramID, "Projection");
	GLuint ViewID = glGetUniformLocation(ProgramID, "View");
	GLuint ModelID = glGetUniformLocation(ProgramID, "Model");

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	/*temp*/
	while(App.IsClosed() == false) {
		/*temp*/
		getDeltaTime();
		// std::cout << 1 / DeltaTime << std::endl;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(ProgramID);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glm::mat4 Model = glm::mat4(1.0f);

		glUniformMatrix4fv(ProjectionID, 1, GL_FALSE, &Player.GiveProjection()[0][0]);
		glUniformMatrix4fv(ViewID, 1, GL_FALSE, &Player.GiveView()[0][0]);
		glUniformMatrix4fv(ModelID, 1, GL_FALSE, &Model[0][0]);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, Map.GiveGlVertexBuffer());
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
		glDrawArrays(GL_TRIANGLES, 0, Map.GiveVertexBufferSize());
		glDisableVertexAttribArray(0);

		Player.Movements(App.GiveWindow());
		/*temp*/
	}
}

void DestroyTextures() {
	//don't forget to implement it
	//glDeleteTextures(1, &texture);
}