#ifndef MATERIAL_H
#define MATERIAL_H
#include "../Shader.h"
class Renderer;
class Material
{
friend Renderer;
public:
	Shader* shader = nullptr;

	Material() 
	{

	}

	Material(Shader* assignedShader) 
	{
		shader = assignedShader;
	}
};
#endif // !MATERIAL_H


