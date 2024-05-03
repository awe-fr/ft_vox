#include <iostream>

#include <View/WindowApp.hpp>

WindowApp::WindowApp(void)
{
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return;
	}
	// glfwWindowHint(GLFW_SAMPLES, 4); // weird white border on textures
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	this->_window = glfwCreateWindow(WIDTH, HEIGHT, "ft_vox", NULL, NULL);
	if (this->_window == NULL) {
		std::cerr << "Failed to to open window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(this->_window);
	glfwSwapInterval( 0 );
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW" << std::endl;
		return;
	}
	glfwSetInputMode(this->_window, GLFW_STICKY_KEYS, GL_TRUE);
}

WindowApp::~WindowApp(void) {}

GLFWwindow	*WindowApp::GiveWindow() {
	return (this->_window);
}

bool	WindowApp::IsClosed() {
	if (glfwGetKey(this->_window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(this->_window) != 0)
		return (true);
	glfwSwapBuffers(this->_window);
	glfwPollEvents();
	return (false);
}