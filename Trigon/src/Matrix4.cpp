#include "Math/Matrix4.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

Matrix4& 
Matrix4::Translate(const Vector3& rhs)
{
	position += rhs;
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
	glm::mat4 translationMat	= glm::translate(glm::vec3(position.x, position.y, position.z));
	glm::mat4 scaleMat			= glm::scale(glm::vec3(scale.x, scale.y, scale.z));
	glm::mat4 rotationMat		= glm::mat4(1.0f);

	data = translationMat * rotationMat * scaleMat;
}