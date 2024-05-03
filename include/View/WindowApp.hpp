#pragma once

#include "ViewVars.hpp"

class	WindowApp {
	private:
		GLFWwindow	*_window;
	public:
		WindowApp(void);
		~WindowApp(void);

		GLFWwindow	*GiveWindow();
		bool		IsClosed();
};