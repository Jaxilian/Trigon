#ifndef MODELMANAGER_H
#define MODELMANAGER_H
#include "Core/Types/Model.h"

class ModelManager
{
private:

public:
	static Model* CreateModel(Mesh* mesh);
	static Model* CreateModel(Mesh* mesh, Material* material);
	static Model* LoadModel(const char* path);
};

#endif

