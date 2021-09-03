#ifndef VECTOR3_H
#define VECTOR3_H


class Vector3
{
public:
	float data[3]{0,0,0};

	float& x = data[0];
	float& y = data[1];
	float& z = data[2];

	float& operator[] (const int& rhs)
	{
		return data[0];
	}

	Vector3& operator = (const Vector3& rhs)
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;

		return *this;
	}

	Vector3& operator - (const Vector3& rhs) 
	{
		Vector3 vec;
		vec.x = x - rhs.x;
		vec.y = y - rhs.y;
		vec.z = z - rhs.z;
		return vec;
	}

	Vector3& operator += (const Vector3& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	Vector3 operator * (const float& rhs)
	{
		Vector3 vec;
		vec.x = x * rhs;
		vec.y = y * rhs;
		vec.z = z * rhs;
		return vec;
	}

	Vector3& operator -() 
	{
		this->x = x * -1;
		this->y = y * -1;
		this->z = z * -1;
		return *this;
	}

	bool operator == (const Vector3& rhs) 
	{
		return x == rhs.x && y == rhs.y && z == rhs.z;
	}

	Vector3(float x, float y, float z);
	Vector3();

	float	 Dot(const Vector3& rhs);
	Vector3& Normalize();
	Vector3& Cross(const Vector3& rhs);
	Vector3& Invert();

	static Vector3	Cross(const Vector3& lhs, const Vector3& rhs);
	static float	Dot(const Vector3& lhs, const Vector3& rhs);

};



#endif // !VECTOR3_H
