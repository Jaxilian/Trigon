#ifndef MATRIX4_H
#define MATRIX4_H

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include "Vector3.h"

class RendererGL;

class Matrix4
{
friend RendererGL;
private:
	glm::mat4	data = glm::mat4(1.0f);
	glm::mat4	translationMat;
	glm::mat4	orientationMat;
	glm::mat4	scaleMat;
	Vector3		degrees;

public:
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;

	Vector3 forward;
	Vector3 up;
	Vector3 right;

	Matrix4& operator = (const Matrix4& rhs)
	{
		data = rhs.data;
		return *this;
	};

	Matrix4& operator * (const Matrix4& rhs) 
	{
		data = data * rhs.data;
		return *this;
	}



	Matrix4& Translate		(const Vector3& rhs);
	Matrix4& LookAt			(const Vector3& target, const Vector3& up);
	Matrix4& SetProjection	(float radians, float width, float height, float near, float far);
	Matrix4& Rotate			(const Vector3& rotation);
	Matrix4& SetPosition	(const Vector3& position);
	Matrix4& SetIdentity();

	void ApplyChanges();

	Matrix4();


	
};

#endif // !MATRIX4_H