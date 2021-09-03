#ifndef MODEL_H
#define MODEL_H
#include "Material.h"
#include "Mesh.h"

class Model
{
public:
	const char*			name		=	"New Model";
	Material*			material	=	nullptr;
	std::vector<Mesh*>	meshes;

	Model() {};
};

#endif // !MODEL_H
