#ifndef MATRIX4_H
#define MATRIX4_H

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>

class Matrix4
{
private:
	glm::mat4 data;

public:

	Matrix4& operator = (const Matrix4& rhs)
	{
		data = rhs.data;
		return *this;
	};


	
};

#endif // !MATRIX4_H