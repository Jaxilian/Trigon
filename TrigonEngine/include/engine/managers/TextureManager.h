#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include "Core/Types/Texture2D.h"

class TextureManager
{
public:
	static Texture2D* CreateTexture(const char* path);
	static void		  DestroyTexture(Texture2D* texture);

};

#endif // !TEXTUREMANAGER_H
