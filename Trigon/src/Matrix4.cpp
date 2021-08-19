#include "Math/Matrix4.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>

Matrix4& 
Matrix4::Translate(const Vector3& rhs)
{
	position += rhs;
	ApplyChanges();
	return *this;
}

Matrix4& 
Matrix4::LookAt(const Vector3& target, const Vector3& up)
{
	data = glm::lookAt
	(
		glm::vec3(position.x, position.y, position.z),
		glm::vec3(target.x, target.y, target.z),
		glm::vec3(up.x, up.y, up.z)
	);

	right.x		= data[0][0];
	right.y		= data[0][1];
	right.z		= data[0][2];

	up.x		= data[1][0];
	up.y		= data[1][1];
	up.z		= data[1][2];

	forward.x	= data[2][0];
	forward.y	= data[2][1];
	forward.z	= data[2][2];


	return *this; 
}

Matrix4& 
Matrix4::Rotate(const Vector3& rotation)
{
	this->rotation += rotation;
	ApplyChanges();
	return *this;
}

Matrix4& 
Matrix4::SetProjection(float radians, float width, float height, float near, float far)
{
	data = glm::perspective(glm::radians(radians), width / height, near, far);
	return *this;
}

Matrix4&
Matrix4::SetPosition(const Vector3& position)
{
	this->position = position;
	ApplyChanges();
	return *this;
}

Matrix4&
Matrix4::SetIdentity() 
{
	data = glm::mat4(1.0f);
	return *this;
}

void 
Matrix4::ApplyChanges() 
{
	forward.x = cos(rotation.x) * sin(rotation.y);
	forward.y = sin(rotation.x);
	forward.z = cos(rotation.x) * cos(rotation.y);


	right.x = sin(rotation.y - 3.14f / 2.0f);
	right.y = 0;
	right.z = cos(rotation.y - 3.14f / 2.0f);


	up = Vector3::Cross(right, forward);

	data[0][0] = right.x;
	data[0][1] = right.y;
	data[0][2] = right.z;

	data[1][0] = up.x;
	data[1][1] = up.y;
	data[1][2] = up.z;

	data[2][0] = forward.x;
	data[2][1] = forward.y;
	data[2][2] = forward.z;

	data[3][0] = position.x;
	data[3][1] = position.y;
	data[3][2] = position.z;

	/*
	glm::mat4 translationMat	= glm::translate(glm::vec3(position.x, position.y, position.z));
	glm::mat4 scaleMat			= glm::scale(glm::vec3(scale.x, scale.y, scale.z));
	glm::mat4 rotationXMat		= glm::rotate(rotation.x, glm::vec3(1, 0, 0));
	glm::mat4 rotationYMat		= glm::rotate(rotation.y, glm::vec3(0, 1, 0));
	glm::mat4 rotationZMat		= glm::rotate(rotation.z, glm::vec3(0, 0, 1));

	data = translationMat * (rotationXMat * rotationYMat * rotationZMat) * scaleMat;

	forward.x = sin(rotation.y);
	forward.y = -tan(rotation.x);
	forward.z = cos(rotation.y);

	forward.Normalize();


	this->right.x = right.x;
	this->right.y = right.y;
	this->right.z = right.z;

	this->up.x = up.x;
	this->up.y = up.y;
	this->up.z = up.z;

	*/

}

Matrix4::Matrix4() 
{
	scale		= Vector3(1, 1, 1);
	rotation	= Vector3(0, 0, 0);
	position	= Vector3(0, 0, 0);
}