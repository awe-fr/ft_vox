#include "../headers/major.h"

int	main() {
	WindowApp App;
	App.InitWindow();
	while(glfwGetKey(App.GiveWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(App.GiveWindow()) == 0) {
		glfwSwapBuffers(App.GiveWindow());
		glfwPollEvents();
	}
}