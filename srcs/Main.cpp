#include "../headers/Major.h"

float	DeltaTime;

void getDeltaTime() {
	static double last = glfwGetTime();

	double now = glfwGetTime();
	DeltaTime = (float)(now - last);
	last = now;
}

/*temp*/
static const GLfloat g_vertex_buffer_data[] = {
	0.0f,0.0f,0.0f, // triangle 1 : begin
	0.0f,0.0f, 1.0f,
	0.0f, 1.0f, 1.0f, // triangle 1 : end
	1.0f, 1.0f,0.0f, // triangle 2 : begin
	0.0f,0.0f,0.0f,
	0.0f, 1.0f,0.0f, // triangle 2 : end
	1.0f,0.0f, 1.0f,
	0.0f,0.0f,0.0f,
	1.0f,0.0f,0.0f,
	1.0f, 1.0f,0.0f,
	1.0f,0.0f,0.0f,
	0.0f,0.0f,0.0f,
	0.0f,0.0f,0.0f,
	0.0f, 1.0f, 1.0f,
	0.0f, 1.0f,0.0f,
	1.0f,0.0f, 1.0f,
	0.0f,0.0f, 1.0f,
	0.0f,0.0f,0.0f,
	0.0f, 1.0f, 1.0f,
	0.0f,0.0f, 1.0f,
	1.0f,0.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,0.0f,0.0f,
	1.0f, 1.0f,0.0f,
	1.0f,0.0f,0.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,0.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f,0.0f,
	0.0f, 1.0f,0.0f,
	1.0f, 1.0f, 1.0f,
	0.0f, 1.0f,0.0f,
	0.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f,
	1.0f,0.0f, 1.0f
};

static const GLfloat g_color_buffer_data[] = {
	0.583f,  0.771f,  0.014f,
	0.609f,  0.115f,  0.436f,
	0.327f,  0.483f,  0.844f,
	0.822f,  0.569f,  0.201f,
	0.435f,  0.602f,  0.223f,
	0.310f,  0.747f,  0.185f,
	0.597f,  0.770f,  0.761f,
	0.559f,  0.436f,  0.730f,
	0.359f,  0.583f,  0.152f,
	0.483f,  0.596f,  0.789f,
	0.559f,  0.861f,  0.639f,
	0.195f,  0.548f,  0.859f,
	0.014f,  0.184f,  0.576f,
	0.771f,  0.328f,  0.970f,
	0.406f,  0.615f,  0.116f,
	0.676f,  0.977f,  0.133f,
	0.971f,  0.572f,  0.833f,
	0.140f,  0.616f,  0.489f,
	0.997f,  0.513f,  0.064f,
	0.945f,  0.719f,  0.592f,
	0.543f,  0.021f,  0.978f,
	0.279f,  0.317f,  0.505f,
	0.167f,  0.620f,  0.077f,
	0.347f,  0.857f,  0.137f,
	0.055f,  0.953f,  0.042f,
	0.714f,  0.505f,  0.345f,
	0.783f,  0.290f,  0.734f,
	0.722f,  0.645f,  0.174f,
	0.302f,  0.455f,  0.848f,
	0.225f,  0.587f,  0.040f,
	0.517f,  0.713f,  0.338f,
	0.053f,  0.959f,  0.120f,
	0.393f,  0.621f,  0.362f,
	0.673f,  0.211f,  0.457f,
	0.820f,  0.883f,  0.371f,
	0.982f,  0.099f,  0.879f
};
/*temp*/

int	main() {
	WindowApp	App;
	PlayerInfo	Player;
	if (App.InitWindow() == true)
		exit(1);
	Player.InitPlayer();

	/*temp*/
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

	GLuint	ProgramID = LoadShaders("./shaders/shader.vert", "./shaders/shader.frag");
	
	GLuint ProjectionID = glGetUniformLocation(ProgramID, "Projection");
	GLuint ViewID = glGetUniformLocation(ProgramID, "View");
	GLuint ModelID = glGetUniformLocation(ProgramID, "Model");

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	/*temp*/
	while(App.IsClosed() == false) {
		/*temp*/
		getDeltaTime();
		std::cout << 1 / DeltaTime << std::endl;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(ProgramID);

		// glEnableVertexAttribArray(0);
		// glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
		// glDrawArrays(GL_TRIANGLES, 0, 3 * 12);
		// glDisableVertexAttribArray(0);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		Player.Movements(App.GiveWindow());
		glm::mat4 Model = glm::mat4(1.0f);
		for (float i = 0; i < 16; i += 1) {
			for (float y = 0; y < 16; y += 1) {
				for (float y = 0; y < 16; y += 1) {
					glUniformMatrix4fv(ProjectionID, 1, GL_FALSE, &Player.GiveProjection()[0][0]);
					glUniformMatrix4fv(ViewID, 1, GL_FALSE, &Player.GiveView()[0][0]);
					glUniformMatrix4fv(ModelID, 1, GL_FALSE, &Model[0][0]);

					glEnableVertexAttribArray(0);
					glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
					glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
					glDrawArrays(GL_TRIANGLES, 0, 3 * 12);
					glDisableVertexAttribArray(0);
					Model = glm::translate(Model, glm::vec3(0, 0, 2));
				}
				glUniformMatrix4fv(ProjectionID, 1, GL_FALSE, &Player.GiveProjection()[0][0]);
				glUniformMatrix4fv(ViewID, 1, GL_FALSE, &Player.GiveView()[0][0]);
				glUniformMatrix4fv(ModelID, 1, GL_FALSE, &Model[0][0]);

				glEnableVertexAttribArray(0);
				glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
				glDrawArrays(GL_TRIANGLES, 0, 3 * 12);
				glDisableVertexAttribArray(0);
				Model = glm::translate(Model, glm::vec3(0, 2, -32));
			}
			glUniformMatrix4fv(ProjectionID, 1, GL_FALSE, &Player.GiveProjection()[0][0]);
			glUniformMatrix4fv(ViewID, 1, GL_FALSE, &Player.GiveView()[0][0]);
			glUniformMatrix4fv(ModelID, 1, GL_FALSE, &Model[0][0]);

			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
			glDrawArrays(GL_TRIANGLES, 0, 3 * 12);
			glDisableVertexAttribArray(0);
			Model = glm::translate(Model, glm::vec3(2, -32, 0));
		}
		/*temp*/
	}
}