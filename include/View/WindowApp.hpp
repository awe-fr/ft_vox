#pragma once

#include "ViewVars.hpp"

class	WindowApp {
	private:
		GLFWwindow	*_window;
	public:
		GLFWwindow	*GiveWindow();
		bool		InitWindow();
		bool		IsClosed();
};