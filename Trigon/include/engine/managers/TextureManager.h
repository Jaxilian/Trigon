#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include "Core/Types/Texture2D.h"
#include <vector>

class TextureManager
{
private:
public:
	static Texture2D* CreateTexture(const char* path);
	static void		  DestroyTexture(Texture2D* texture);

};

#endif // !TEXTUREMANAGER_H
