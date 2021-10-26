#ifndef modelmanager_h
#define modelmanager_h
#include <vector>
#include "common/model.h"
#include "common/Texture2D.h"

namespace modelmanager
{
    bool LoadObj(const char* path,const char* matPath, Model* model, bool indexed);
    bool LoadTex(const char* path, Texture2D* outTexture);
    void clearTexture(Texture2D* tex);
}

#endif