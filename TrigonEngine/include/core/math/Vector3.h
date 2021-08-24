#ifndef VECTOR3_H
#define VECTOR3_H

#include "glm/vec3.hpp"

class Vector3
{
private:
	glm::vec3 data = glm::vec3(0.0f);

public:
	float& x = data.x;
	float& y = data.y;
	float& z = data.z;

	Vector3& operator += (const Vector3& rhs) 
	{
		data += rhs.data;
		return *this;
	}

	Vector3& operator = (const Vector3& rhs) 
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		return *this;
	}

	Vector3 operator * (const float& rhs) 
	{
		Vector3 vec;
		vec.data = data * rhs;
		return vec;
	}
	
	Vector3& Normalize();
	
	static Vector3 Cross(const Vector3& lhs, const Vector3& rhs);

	Vector3();
	Vector3(float x, float y, float z);


};

#endif // !VECTOR3_H
