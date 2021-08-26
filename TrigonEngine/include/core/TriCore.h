#ifndef TRICORE_H
#define TRICORE_H
enum KeyCode
{
	KEY_0 = 48, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9,
	A = 65, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
	ESCAPE = 256, ENTER, TAB, BACKSPACE, INSERT, DELETE, RIGHT, LEFT, DOWN, UP, PAGE_UP,
	PAGE_DOWN, HOME, END, CAPS_LOCK, SCROLL_LOCK, NUM_LOCK, PAUSE,
	F1 = 290, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13, F14, F15, F16, F17, F18, F19, F20, F21, F22, F23, F25,
	KEY_PAD_0 = 320, KEY_PAD_1, KEY_PAD_2, KEY_PAD_3, KEY_PAD_4, KEY_PAD_5, KEY_PAD_6, KEY_PAD_7, KEY_PAD_8,
	KEY_PAD_9, KEY_PAD_DECIAMAL, KEY_PAD_DIVIDE, KEY_PAD_MULTIPLY, KEY_PAD_SUBTRACT, KEY_PAD_ADD,
	KEY_PAD_ENTER, KEY_PAD_EQUAL, LEFT_SHIFT = 340, LEFT_CONTROL, LEFT_ALT, LEFT_SUPER, RIGHT_SHIFT, RIGHT_CONTROL,
	RIGHT_ALT, RIGHT_SUPER, MENU, SPACE = 32
};


#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32

#include "glad/gl.h"
#include "GLFW/glfw3.h"
#include "backend/Debug.h"

#endif // !TRICORE_H
