#ifndef MATERIAL_H
#define MATERIAL_H
#include <string>
#include <glm/vec3.hpp>
#include "Texture2D.h"

struct Mesh;

struct Material
{
    std::string name;
    uint32_t    programID;
    bool        glBinded;

    static glm::vec3 lightDir;

    Texture2D albedoTexture;

    unsigned int M;
    unsigned int V;
    unsigned int P;
    unsigned int L;

    unsigned int albedo;

    void onCreation();

    void OnDraw(Mesh* mesh);
};

#endif