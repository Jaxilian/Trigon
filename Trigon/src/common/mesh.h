#ifndef MESH_H
#define MESH_H
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <memory>
#include "material.h"

struct Model;

struct Mesh
{
    std::string                 name;
    std::vector<glm::vec3>      positions;
    std::vector<glm::vec3>      normals;
    std::vector<glm::vec3>      colors;
    std::vector<glm::vec2>      uvs;
    std::vector<uint32_t>       indices;
    std::shared_ptr<Material>   material;
    Model&                      parent;

    bool                    indexed;
    bool                    glBinded;
    unsigned int            glVertexBuffer;
    unsigned int            glColorBuffer;
    unsigned int            glIndexBuffer;
    unsigned int            glNormalBuffer;
    unsigned int            glUvBuffer;

    Mesh(Model& rParent) : parent(rParent){};
};

#endif