#include "core/math/Matrix4.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/euler_angles.hpp>

Matrix4& 
Matrix4::Translate(const Vector3& rhs)
{
	position += rhs;
	return *this;
}

Matrix4& 
Matrix4::LookAt(const Vector3& target, const Vector3& up)
{
	orientationMat = glm::lookAt
	(
		glm::vec3(position.x, position.y, position.z),
		glm::vec3(target.x, target.y, target.z),
		glm::vec3(up.x, up.y, up.z)
	);


	return *this; 
}

Matrix4& 
Matrix4::Rotate(const Vector3& rotation)
{
	this->rotation += rotation;
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
	glm::mat4 transform = glm::mat4(1.0f);
	scaleMat		= glm::scale(transform,glm::vec3(scale.x, scale.y, scale.z));
	orientationMat	= glm::eulerAngleXYZ(glm::radians(rotation.x), glm::radians(rotation.y), glm::radians(rotation.z));
	translationMat	= glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, position.z));


	data =  orientationMat * translationMat * scaleMat;

	const glm::mat4 inverted	= glm::inverse(data);
	const glm::vec3 forward		= glm::normalize(glm::vec3(inverted[2]));
	const glm::vec3 right		= glm::normalize(glm::vec3(inverted[0]));
	const glm::vec3 up			= glm::normalize(glm::vec3(inverted[1]));

	this->forward.x = forward.x;
	this->forward.y = forward.y;
	this->forward.z = forward.z;

	this->right.x	= right.x;
	this->right.y	= right.y;
	this->right.z	= right.z;

	this->up.x		= up.x;
	this->up.y		= up.y;
	this->up.z		= up.z;
}

Matrix4::Matrix4() 
{
	translationMat	= glm::mat4(1.0f);
	orientationMat	= glm::mat4(1.0f);
	scaleMat		= glm::mat4(1.0f);
	scale		= Vector3(1, 1, 1);
	rotation	= Vector3(0, 0, 0);
	position	= Vector3(0, 0, 0);
	right		= Vector3(1, 0, 0);
	up			= Vector3(0, 1, 0);
	forward		= Vector3(0, 0, 1);
}