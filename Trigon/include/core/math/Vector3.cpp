#include "Vector3.h"
#include <math.h>

Vector3::Vector3()
{
	x = 0;
	y = 0;
	z = 0;
}

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

float
Vector3::Dot(const Vector3& rhs)
{
	return x * rhs.x + y * rhs.y + z * rhs.z;
}

Vector3& 
Vector3::Normalize()
{
	double mag = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	x = x / mag;
	y = y / mag;
	z = z / mag;
	return *this;
}

Vector3&
Vector3::Cross(const Vector3& rhs)
{

	x = y * rhs.z - z * rhs.y;
	y = z * rhs.x - x * rhs.z;
	z = x * rhs.y - y * rhs.x;

	return *this;
}

Vector3&
Vector3::Invert()
{
	x = x * -1;
	y = y * -1;
	z = z * -1;
	return *this;
}

 Vector3 
 Vector3::Cross(const Vector3& lhs, const Vector3& rhs)
{
	 Vector3 vec;
	 vec.x = lhs.y * rhs.z - lhs.z * rhs.y;
	 vec.y = lhs.z * rhs.x - lhs.x * rhs.z;
	 vec.z = lhs.x * rhs.y - lhs.y * rhs.x;
	 return vec;
}

float	
Vector3::Dot(const Vector3& lhs, const Vector3& rhs)
 {
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
 }