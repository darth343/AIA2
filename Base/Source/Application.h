#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"
#include <irrKlang.h>

using namespace irrklang;
struct GLFWwindow;

class Application
{
public:
	static Application& GetInstance()
	{
		static Application app;
		return app;
	}
	void Init();
	void Run();
	void Exit();

	void UpdateInput();
	void PostInputUpdate();
	
	static void MouseButtonCallbacks(GLFWwindow* window, int button, int action, int mods);
	static void MouseScrollCallbacks(GLFWwindow* window, double xoffset, double yoffset);

	int GetWindowHeight();
	int GetWindowWidth();
	ISoundEngine* m_soundEngine;

private:
	Application();
	~Application();

	static bool IsKeyPressed(unsigned short key);

	// Should make these not hard-coded :P
	const static int m_window_width = 1200;
	const static int m_window_height = 900;

	//Declare a window object
	StopWatch m_timer;
	GLFWwindow* m_window;
};

#endif