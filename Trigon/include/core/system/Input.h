#ifndef INPUT_H
#define INPUT_H
#include "WindowManager.h"
#include "../math/Vector2.h"
#include "../TriCore.h"

class Input
{
private:
	static float cursorX;
	static float cursorY;
	static bool  lockCursor;

public:
	static bool		GetKey(KeyCode keycode);

	static Vector2  GetMousePosition();

	static void		SetMousePosition(Vector2 mousePos);

	static void		SetCursorLockState(bool value);
	static bool		GetCursorLockState();

	static Vector2	GetMouseAxis();


};
#endif // !INPUT_H