#ifndef MATERIAL_H
#define MATERIAL_H
#include "../Shader.h"
class Renderer;
class Material
{
friend Renderer;
private:
	Shader* shader = nullptr;

public:
	Material(Shader* assignedShader) 
	{
		shader = assignedShader;
	}
};
#endif // !MATERIAL_H


