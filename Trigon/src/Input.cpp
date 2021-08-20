#include "Core/Input.h"
#include "Core/WindowManager.h"

float Input::cursorX;
float Input::cursorY;
bool  Input::lockCursor;

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

void
Input::SetMousePosition(Vector2 mousePos)
{
	glfwSetCursorPos(WindowManager::GetInstance()->window, mousePos.x, mousePos.y);
}

Vector2
Input::GetMouseAxis() 
{
	Vector2 diff;
	Vector2 curPos = GetMousePosition();
	if (lockCursor) SetMousePosition(Vector2(WindowManager::GetInstance()->width / 2, WindowManager::GetInstance()->height / 2));

	diff.x = WindowManager::GetInstance()->width / 2 - curPos.x;
	diff.y = WindowManager::GetInstance()->height / 2 - curPos.y;

	return diff;
}
 
void		
Input::SetCursorLockState(bool value) 
{
	lockCursor = value;
	switch (value)
	{
	case true:
		glfwSetInputMode(WindowManager::GetInstance()->window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		break;
	case false:
		glfwSetInputMode(WindowManager::GetInstance()->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		break;
	default:
		break;
	}
}

bool		
Input::GetCursorLockState()
{
	return lockCursor;
}