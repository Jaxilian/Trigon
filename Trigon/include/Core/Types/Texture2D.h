#ifndef TEXTURE2D_H
#define TEXTURE2D_H
class Renderer;
class TextureManager;
class Texture2D
{
	friend Renderer;
	friend TextureManager;
private:
	unsigned int	location;
public:
	int				width;
	int				height;
	int				channels;
	unsigned char*	image;
};

#endif // !TEXTURE2D_H


