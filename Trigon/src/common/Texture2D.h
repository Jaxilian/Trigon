#ifndef TEXTURE2D
#define TEXTURE2D

struct Texture2D
{
    int width;
    int height;
    int channels;
    unsigned char*  data;
    
    unsigned int    glTextureID;
    bool            glBinded;
};

#endif