#ifndef EDITORGUI_H
#define EDITORGUI_H
#include "imgui.h"
#include "Editor/Panels/PInspector.h"

class EditorGUI
{
private:
	PInspector inspector;

public:
	 EditorGUI();
	 void Save();
	 void Draw();
	~EditorGUI();

};

#endif // !EDITGUI_H
