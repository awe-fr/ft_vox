#include "../headers/WindowApp.hpp"

bool	WindowApp::InitWindow() {
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return (true);
	}
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	this->_window = glfwCreateWindow(WIDTH, HEIGHT, "ft_vox", NULL, NULL);
	if (this->_window == NULL) {
		std::cerr << "Failed to to open window" << std::endl;
		glfwTerminate();
		return (true);
	}
	glfwMakeContextCurrent(this->_window);
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW" << std::endl;
		return (true);
	}
	glfwSetInputMode(this->_window, GLFW_STICKY_KEYS, GL_TRUE);
	return (false);
}

GLFWwindow	*WindowApp::GiveWindow() {
	return (this->_window);
}