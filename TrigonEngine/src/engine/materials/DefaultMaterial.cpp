#include "engine/materials/DefaultMaterial.h"
#include "engine/managers/TextureManager.h"
DefaultMaterial::DefaultMaterial() 
{
	shader = new Shader("assets/shaders/defaultVertex.glsl", "assets/shaders/defaultPixel.glsl");
	CreateUniformMatices();

	albedo				= TextureManager::CreateTexture("assets/Speedprop_Door_BaseColor.tga");
	metallic			= TextureManager::CreateTexture("assets/Speedprop_Door_Metallic.tga");
	normal				= TextureManager::CreateTexture("assets/Speedprop_Door_Normal.tga");
	roughness			= TextureManager::CreateTexture("assets/Speedprop_Door_Roughness.tga");
	ambientOcclusion	= TextureManager::CreateTexture("assets/Speedprop_Door_ambient.tga");

	shader->AddUniformTex2D("albedoMap",	albedo);
	shader->AddUniformTex2D("normalMap",	normal);
	shader->AddUniformTex2D("metallicMap",	metallic);
	shader->AddUniformTex2D("roughnessMap", roughness);
	shader->AddUniformTex2D("aoMap",		ambientOcclusion);
}


