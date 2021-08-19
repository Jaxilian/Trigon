#include "Math/Vector3.h"
#include "glm/gtx/normalize_dot.hpp"

Vector3&
Vector3::Normalize() 
{
	data = glm::normalize(data);
	return *this;
}

Vector3::Vector3()
{
	x = 0;
	y = 0;
	z = 0;
};

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
};

Vector3 
Vector3::Cross(const Vector3& lhs, const Vector3& rhs)
{
	Vector3 vec;
	vec.data = glm::cross(lhs.data, rhs.data);
	return vec;
}