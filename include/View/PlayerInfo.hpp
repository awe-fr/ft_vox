#pragma once

#include "ViewVars.hpp"
#include <array>

class	PlayerInfo {
	private:
		glm::mat4	_Projection;
		glm::mat4	_View;
		glm::vec3	_Direction;
		glm::vec3	_Position;
		glm::vec3	_Right;
		glm::vec3	_Up;
		float		_HorizontalAngle;
		float		_VerticalAngle;
		float		_MouseSpeed;
		float		_Speed;
		float		_FOV;
	public:
		PlayerInfo(void);
		~PlayerInfo(void);
		
		glm::mat4	GiveProjection();
		glm::mat4	GiveView();
		glm::vec3	GiveDirection();
		glm::vec3	GivePosition();
		glm::vec3	GiveUp();
		float		GiveFOV();
		void		Movements(GLFWwindow *Window);
		std::array<int, 2> getChunkPos(void);
};