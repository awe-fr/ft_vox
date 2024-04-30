#pragma once

#include "ViewVars.hpp"

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
		glm::mat4	GiveProjection();
		glm::mat4	GiveView();
		void		Movements(GLFWwindow *Window);
		void		InitPlayer();
};