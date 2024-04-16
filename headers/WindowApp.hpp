#pragma once

#include "major.h"

class WindowApp {
	private:
		GLFWwindow	*_window;
	public:
		bool	InitWindow();
		GLFWwindow	*GiveWindow();
};