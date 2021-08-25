#ifndef INSPECTORPANEL_H
#define INSPECTORPANEL_H

#include "engine/entities/Entity.h"

class InspectorPanel 
{
public:

	static InspectorPanel* instance;
	Entity* currentEntity = nullptr;

	InspectorPanel();

	void SetEntity(Entity* entity);

	void Draw();
};
#endif // !INSPECTORPANEL_H
