#include "Material.h"

Material::Material()
{
	
}

void
Material::CreateUniformMatices() 
{
	shader->AddUniformMat4f("ModelTransform", nullptr);
	shader->AddUniformMat4f("CameraTransform", nullptr);
	shader->AddUniformMat4f("ProjectionMatrix", nullptr);
}

void
Material::UpdateMatrices(Matrix4* model, Matrix4* camera, Matrix4* projection)
{
	shader->SetUniformMat4f("ModelTransform", model);
	shader->SetUniformMat4f("CameraTransform", camera);
	shader->SetUniformMat4f("ProjectionMatrix", projection);
}