#ifndef MATERIAL_H
#define MATERIAL_H
#include "Shader.h"
#include "Material.h"
#include "../math/Matrix4.h"
class Renderer;
class Material
{
friend Renderer;
public:
	Shader* shader = nullptr;

	Material();

	Material(Shader* assignedShader) 
	{
		shader = assignedShader;
	}
	void CreateUniformMatices();
	void UpdateMatrices(Matrix4* model, Matrix4* camera, Matrix4* projection);
};
#endif // !MATERIAL_H


