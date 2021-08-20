#include "Engine/Managers/TextureManager.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Core/core.h"
#include "Core/Renderer.h"

Texture2D* TextureManager::CreateTexture(const char* path) 
{
	Texture2D* texture = new Texture2D();

	texture->image = stbi_load(path, &texture->width, &texture->height, &texture->channels, 0);

	if (texture->image == NULL)
	{
		Debug::LogError("Failed to load image!\n");
		delete texture;
		return nullptr;
	}

	texture->location = Renderer::BindTexture2D(texture);


	return texture;
}

void	
TextureManager::DestroyTexture(Texture2D* texture)
{
	Renderer::UnbindTexture2D(texture);
	delete texture;
	texture = nullptr;
}