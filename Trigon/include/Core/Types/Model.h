#ifndef MODEL_H
#define MODEL_H
#include "Material.h"
#include "Mesh.h"

class Model
{
public:
	Material*	material;
	Mesh*		mesh;

	Model() {};
};

#endif // !MODEL_H
