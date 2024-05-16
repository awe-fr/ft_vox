#include <View/PlayerInfo.hpp>

extern float  delta_time;

PlayerInfo::PlayerInfo(void)
{
	this->_HorizontalAngle = 0;
	this->_VerticalAngle = 0;
	this->_MouseSpeed = 0.005f;
	this->_Speed = 5.0f;
	this->_FOV = 80;
	this->_Position = {0.f, 80.f, 0.f};
	this->_Direction = {cos(this->_VerticalAngle) * sin(this->_HorizontalAngle), sin(this->_VerticalAngle), cos(this->_VerticalAngle) * cos(this->_HorizontalAngle)};
	this->_Right = {sin(this->_HorizontalAngle - 3.14f/2.0f), 0, cos(this->_HorizontalAngle - 3.14f/2.0f)};
	this->_Up = glm::cross(this->_Right, this->_Direction);
	this->_Projection = glm::perspective(glm::radians(this->_FOV), (float) WIDTH / (float)HEIGHT, 0.1f, 1000.0f);
	this->_View = glm::lookAt(this->_Position, this->_Position + this->_Direction, this->_Up);
}

PlayerInfo::~PlayerInfo(void) {}

glm::mat4	PlayerInfo::GiveProjection() {
	return (this->_Projection);
}

glm::mat4	PlayerInfo::GiveView() {
	return (this->_View);
}

void	PlayerInfo::Movements(GLFWwindow *Window) {
	if (glfwGetKey(Window, GLFW_KEY_W) == GLFW_PRESS)
		this->_Position += this->_Direction * delta_time * this->_Speed;
	if (glfwGetKey(Window, GLFW_KEY_S) == GLFW_PRESS)
		this->_Position -= this->_Direction * delta_time * this->_Speed;
	if (glfwGetKey(Window, GLFW_KEY_D) == GLFW_PRESS)
		this->_Position += this->_Right * delta_time * this->_Speed;
	if (glfwGetKey(Window, GLFW_KEY_A) == GLFW_PRESS)
		this->_Position -= this->_Right * delta_time * this->_Speed;
	if (glfwGetKey(Window, GLFW_KEY_SPACE) == GLFW_PRESS)
		this->_Position += this->_Up * delta_time * this->_Speed;
	if (glfwGetKey(Window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		this->_Position -= this->_Up * delta_time * this->_Speed;
	if (glfwGetKey(Window, GLFW_KEY_UP) == GLFW_PRESS)
		this->_VerticalAngle += 1 * delta_time;
	if (glfwGetKey(Window, GLFW_KEY_DOWN) == GLFW_PRESS)
		this->_VerticalAngle -= 1 * delta_time;
	if (glfwGetKey(Window, GLFW_KEY_LEFT) == GLFW_PRESS)
		this->_HorizontalAngle += 1 * delta_time;
	if (glfwGetKey(Window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		this->_HorizontalAngle -= 1 * delta_time;
	if (glfwGetKey(Window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		this->_Speed = 100;
	else
		this->_Speed = 5;
	this->_Direction = {cos(this->_VerticalAngle) * sin(this->_HorizontalAngle), sin(this->_VerticalAngle), cos(this->_VerticalAngle) * cos(this->_HorizontalAngle)};
	this->_Right = {sin(this->_HorizontalAngle - 3.14f/2.0f), 0, cos(this->_HorizontalAngle - 3.14f/2.0f)};
	this->_Up = glm::cross(this->_Right, this->_Direction);
	this->_Projection = glm::perspective(glm::radians(this->_FOV), (float) WIDTH / (float)HEIGHT, 0.1f, 500.0f);
	this->_View = glm::lookAt(this->_Position, this->_Position + this->_Direction, this->_Up);

	// std::cout << this->_Position.x << " " << this->_Position.y << " " << this->_Position.z << " " << std::endl;
}

std::array<int, 2> PlayerInfo::getChunkPos(void)
{
	return {(int)this->_Position.x / CHUNK_SIZE, (int)this->_Position.z / CHUNK_SIZE};
}

glm::vec3	PlayerInfo::GiveDirection() {
	return (this->_Direction);
}

glm::vec3	PlayerInfo::GivePosition() {
	return (this->_Position);
}

glm::vec3	PlayerInfo::GiveUp() {
	return (this->_Up);
}

float		PlayerInfo::GiveFOV() {
	return (this->_FOV);
}