#include "Engine/Managers/ModelManager.h"
#include "Core/Renderer.h"

Model* 
ModelManager::CreateModel(Mesh* mesh) 
{
	int bufferLocation		= Renderer::BindBuffer(mesh->vertexBuffer);
	mesh->bufferLocation	= bufferLocation;

	Model* model	=	new Model();
	model->mesh		=	mesh;

	return model;
}

Model* 
ModelManager::CreateModel(Mesh* mesh, Material* material)
{
	int bufferLocation = Renderer::BindBuffer(mesh->vertexBuffer);
	mesh->bufferLocation = bufferLocation;

	Model* model	= new Model();
	model->mesh		= mesh;
	model->material = material;

	return model;
}