#ifndef vertex_h
#define vertex_h
#include "math/Vector3.h"
#include "math/Vector2.h"
struct Vertex
{
    Vector3 position;
    Vector3 normal;
    Vector3 color;
    Vector2 uv;
};

#endif