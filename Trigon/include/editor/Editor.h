#ifndef EDITOR_H
#define EDITOR_H

#include "windows/WindowInspector.h"
#include "windows/WindowHierarchy.h"

class Editor
{
public:

	WindowInspector inspector;
	WindowHierarchy hierarchy;

	 Editor();
	~Editor();

	void Draw();
};

#endif // !EDITOR_H
