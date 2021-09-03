#include "Input.h"
#include "WindowManager.h"

float Input::cursorX;
float Input::cursorY;
bool  Input::lockCursor;

bool 
Input::GetKey(KeyCode keycode)
{
	if (glfwGetKey(WindowManager::GetInstance()->m_pWindow, (int)keycode)) return true;
	return false;
}


Vector2  
Input::GetMousePosition()
{
	double x, y;
	glfwGetCursorPos(WindowManager::GetInstance()->m_pWindow, &x, &y);
	return Vector2(x, y);
}

void
Input::SetMousePosition(Vector2 mousePos)
{
	glfwSetCursorPos(WindowManager::GetInstance()->m_pWindow, mousePos.x, mousePos.y);
}

Vector2
Input::GetMouseAxis() 
{
	Vector2 diff;
	Vector2 curPos = GetMousePosition();
	if (lockCursor) SetMousePosition(Vector2(WindowManager::GetInstance()->m_Width / 2, WindowManager::GetInstance()->m_Height / 2));

	diff.x = WindowManager::GetInstance()->m_Width / 2 - curPos.x;
	diff.y = WindowManager::GetInstance()->m_Height / 2 - curPos.y;

	return diff;
}
 
void		
Input::SetCursorLockState(bool value) 
{
	lockCursor = value;
	switch (value)
	{
	case true:
		glfwSetInputMode(WindowManager::GetInstance()->m_pWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		break;
	case false:
		glfwSetInputMode(WindowManager::GetInstance()->m_pWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
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