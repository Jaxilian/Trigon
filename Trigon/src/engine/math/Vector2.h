#ifndef VECTOR2_H
#define VECTOR2_H
#include "glm/vec2.hpp"
class Vector2
{
public:
    glm::vec2 data;
    float& x = data.x;
    float& y = data.y;

    void cpy(const Vector2& rhs)
    {
        data.x = rhs.x;
        data.y = rhs.y;
    }
};

#endif