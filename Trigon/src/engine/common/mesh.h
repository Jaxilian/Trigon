#ifndef mesh_h
#define mesh_h
#include <vector>
#include "vertex.h"
#include "material.h"

struct Mesh
{
    std::vector<glm::vec3>      positions;
    std::vector<glm::vec3>      normals;
    std::vector<glm::vec3>      colors;
    std::vector<glm::vec2>      uvs;
    std::vector<unsigned int>   indices;
    Material                    material;

    bool         glBinded;
    unsigned int glVertexBuffer;
    unsigned int glColorBuffer;
    unsigned int glIndexBuffer;
    unsigned int glNormalBuffer;
    unsigned int glUvBuffer;
};

#endif