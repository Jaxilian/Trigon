#ifndef VECTOR3_H
#define VECTOR3_H
#include "glm/vec3.hpp"
class Vector3
{
private:

public:
    glm::vec3 data;

    float& x = data[0];
    float& y = data[1];
    float& z = data[2];

    void cpy(const glm::vec3& rhs)
    {
        data.x = rhs.x;
        data.y = rhs.y;
        data.z = rhs.z;
    }
};

#endif