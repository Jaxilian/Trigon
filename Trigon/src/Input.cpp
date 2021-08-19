#include "Core/Input.h"
#include "Core/WindowManager.h"

bool 
Input::GetKey(KeyCode keycode)
{
	if (glfwGetKey(WindowManager::GetInstance()->window, keycode)) return true;
	return false;
}


Vector2  
Input::GetMousePosition()
{
	double x, y;
	glfwGetCursorPos(WindowManager::GetInstance()->window, &x, &y);
	return Vector2(x, y);
}

