#ifndef MODEL_H
#define MODEL_H
#include "mesh.h"
#include "components/transform.h"
#include <vector>

class Entity;

struct Model
{
    std::vector<Mesh>       meshes;
    Transform*              transform = nullptr;
};

#endif