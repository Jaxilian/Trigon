#ifndef GLREND_H
#define GLREND_H
#include "common/model.h"

struct Shader;

namespace glrend
{
    void            create();
    void            clear();
    void            release();
    void            draw(Model& model);
    void            bindMesh(Mesh& mesh);
    void            bindModel(Model& model);

    void            createShader(const char* vertPath, const char* fragPath, Material& outMat);

}


#endif