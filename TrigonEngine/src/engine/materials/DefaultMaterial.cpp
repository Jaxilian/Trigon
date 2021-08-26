#include "engine/materials/DefaultMaterial.h"
#include "engine/managers/TextureManager.h"
DefaultMaterial::DefaultMaterial() 
{
	shader = new Shader("assets/shaders/defaultVertex.glsl", "assets/shaders/defaultPixel.glsl");
	CreateUniformMatices();

	albedo = TextureManager::CreateTexture("assets/Speedprop_Door_BaseColor.tga");
	shader->AddUniformTex2D("textureSampler", albedo);
}


