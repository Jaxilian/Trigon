#ifndef WINDOWINSPECTOR_H
#define WINDOWINSPECTOR_H
#include "Window.h"

class Entity;
class Vector3;

class WindowInspector : public Window
{
public:
	static WindowInspector* instance;
	Entity* currentEntity	= nullptr;
	Vector3* tempPos		= nullptr;
	Vector3* tempRot		= nullptr;
	Vector3* tempScale		= nullptr;

	WindowInspector();

	void SetEntity(Entity* entity);
	
	void Draw() override;
};


#endif // !1