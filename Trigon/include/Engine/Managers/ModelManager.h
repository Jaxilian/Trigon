#ifndef MODELMANAGER_H
#define MODELMANAGER_H
#include "Core/Types/Model.h"

class ModelManager
{
public:
	static Model* CreateModel(Mesh* mesh);
	static Model* CreateModel(Mesh* mesh, Material* material);

};

#endif

