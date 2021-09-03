#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H
#pragma once
#include "../TriCore.h"

struct WindowPtr
{
	GLFWwindow* m_pWindow;
	const char* m_pName;
	int m_Width;
	int m_Height;
};

class WindowManager
{
private:
	static WindowPtr*	ptr;
	static bool			initialized;

public:
	static WindowPtr*	GetInstance();
	static bool			CreateInstance();
	static bool			ReleaseInstance();

};


#endif // !WINDOWMANAGER_H