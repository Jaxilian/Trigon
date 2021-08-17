#ifndef VECTOR3_H
#define VECTOR3_H

#include "glm/vec3.hpp"

class Vector3
{
private:
	glm::vec3 data;

public:
	float& x = data.x;
	float& y = data.y;
	float& z = data.z;


};

#endif // !VECTOR3_H
