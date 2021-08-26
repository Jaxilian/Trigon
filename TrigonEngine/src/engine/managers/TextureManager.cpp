#include "engine/managers/TextureManager.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "core/TriCore.h"
#include "core/backend/Renderer.h"


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

	texture->location = Renderer::GetInstance()->BindTexture2D(texture);


	return texture;
}

void	
TextureManager::DestroyTexture(Texture2D* texture)
{
	Renderer::GetInstance()->ReleaseTexture2D(texture);
	delete texture;
	texture = nullptr;
}