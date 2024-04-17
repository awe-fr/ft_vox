#include "../headers/PlayerInfo.hpp"

void	PlayerInfo::InitPlayer() {
	this->_HorizontalAngle = 0;
	this->_VerticalAngle = 0;
	this->_MouseSpeed = 0.005f;
	this->_Speed = 3.0f;
	this->_FOV = 80;
	this->_Position = {0, 0, 5};
	this->_Direction = {cos(this->_VerticalAngle) * sin(this->_HorizontalAngle), sin(this->_VerticalAngle), cos(this->_VerticalAngle) * cos(this->_HorizontalAngle)};
	this->_Right = {sin(this->_HorizontalAngle - 3.14f/2.0f), 0, cos(this->_HorizontalAngle - 3.14f/2.0f)};
	this->_Up = glm::cross(this->_Right, this->_Direction);
	this->_Projection = glm::perspective(glm::radians(this->_FOV), (float) WIDTH / (float)HEIGHT, 0.1f, 100.0f);
	this->_View = glm::lookAt(this->_Position, this->_Position + this->_Direction, this->_Up);

}

glm::mat4	PlayerInfo::GiveProjection() {
	return (this->_Projection);
}

glm::mat4	PlayerInfo::GiveView() {
	return (this->_View);
}

void	PlayerInfo::Movements(GLFWwindow *Window) {
	if (glfwGetKey(Window, GLFW_KEY_W) == GLFW_PRESS)
		this->_Position += this->_Direction * this->_Speed;
	if (glfwGetKey(Window, GLFW_KEY_S) == GLFW_PRESS)
		this->_Position -= this->_Direction * this->_Speed;
	if (glfwGetKey(Window, GLFW_KEY_D) == GLFW_PRESS)
		this->_Position += this->_Right * this->_Speed;
	if (glfwGetKey(Window, GLFW_KEY_A) == GLFW_PRESS)
		this->_Position -= this->_Right * this->_Speed;
	this->_Projection = glm::perspective(glm::radians(this->_FOV), (float) WIDTH / (float)HEIGHT, 0.1f, 100.0f);
	this->_View = glm::lookAt(this->_Position, this->_Position + this->_Direction, this->_Up);
}