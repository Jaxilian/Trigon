#ifndef TEXTURE2D_H
#define TEXTURE2D_H
class RendererGL;
class TextureManager;

class Texture2D
{
	friend RendererGL;
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