#include "engine/materials/DefaultMaterial.h"
#include "engine/managers/TextureManager.h"
DefaultMaterial::DefaultMaterial() 
{
	shader = new Shader("assets/shaders/defaultVertex.glsl", "assets/shaders/defaultPixel.glsl");
	CreateUniformMatices();

	texture = TextureManager::CreateTexture("assets/GridTex.png");
	shader->AddUniformTex2D("textureSampler", texture);
}


