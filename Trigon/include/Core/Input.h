#ifndef INPUT_H
#define INPUT_H
#include "Core/Core.h"
#include "Math/Vector2.h"

class Input
{
public:
	static bool		GetKey(KeyCode keycode);

	static Vector2  GetMousePosition();

};
#endif // !INPUT_H