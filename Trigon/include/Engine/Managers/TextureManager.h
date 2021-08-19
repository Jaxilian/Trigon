#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include "Core/Types/Texture2D.h"

class TextureManager
{
public:
	static Texture2D* CreateTexture(const char* path);

};

#endif // !TEXTUREMANAGER_H
