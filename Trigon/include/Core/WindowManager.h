#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H
#pragma once
#include "Core.h"

struct WindowPtr
{
	GLFWwindow* window;
	const char* name;
	int width;
	int height;
};

class WindowManager
{
private:
	static WindowPtr*	ptr;
	static bool			initialized;

public:
	static WindowPtr* GetInstance();
	static bool			CreateInstance();
	static bool			ReleaseInstance();

};


#endif // !WINDOWMANAGER_H