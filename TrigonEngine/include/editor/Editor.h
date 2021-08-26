#ifndef EDITOR_H
#define EDITOR_H
#include "backend/imgui.h"
#include "panels/InspectorPanel.h"
#include "panels/HierarchyPanel.h"

class Editor
{
private:
	InspectorPanel	inspector;
	HierarchyPanel	hierarchy;

public:
	 Editor();
	~Editor();

	void BeginDraw();
	void Draw();
	void EndDraw();
};

#endif // !EDITOR_H
