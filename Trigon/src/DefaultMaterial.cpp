#include "Engine/Materials/DefaultMaterial.h"
#include "Engine/Managers/TextureManager.h"
#include "Core/Renderer.h"

DefaultMaterial* DefaultMaterial::instance;

DefaultMaterial::DefaultMaterial()
{
	shader	= new Shader("shaders/defaultVertex.glsl", "shaders/defaultPixel.glsl");
	texture	= TextureManager::CreateTexture("assets/GridTex.png");

	shader->AddUniformTex2D("textureSampler", texture);
	shader->AddUniformMat4f("ModelTransform", modelMatrix);
	shader->AddUniformMat4f("CameraTransform", cameraMatrix);
	shader->AddUniformMat4f("ProjectionMatrix", projection);

	instance = this;
}

void 
DefaultMaterial::UpdateValues(Camera* camera, Matrix4* modelMatrix)
{
	this->modelMatrix	= modelMatrix;
	this->cameraMatrix	= &camera->transform;
	this->projection	= &camera->projection;

	shader->SetUniformMat4f("ModelTransform", modelMatrix);
	shader->SetUniformMat4f("CameraTransform", cameraMatrix);
	shader->SetUniformMat4f("ProjectionMatrix", projection);
	shader->SetUniformTex2D("textureSampler", texture);
}

DefaultMaterial::~DefaultMaterial() 
{
	instance = nullptr;
	TextureManager::DestroyTexture(texture);
	Renderer::UnbindShader(shader);
}