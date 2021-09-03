#ifndef WINDOW_H
#define WINDOW_H
#include "../backend/imgui_single_file.h"
#include "../backend/imgui.h"

class Window
{
public:
	virtual void Draw();
};

#endif // !WINDOW_H