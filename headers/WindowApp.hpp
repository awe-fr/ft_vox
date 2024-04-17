#pragma once

#include "Major.h"

class WindowApp {
	private:
		GLFWwindow	*_window;
	public:
		GLFWwindow	*GiveWindow();
		bool	InitWindow();
		bool	IsClosed();
};