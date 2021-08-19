#include "Core/Camera.h"
#include "Core/WindowManager.h"
Camera* Camera::currentCamera = nullptr;

Camera::Camera(float _radians, float _near, float _far)
{
	if (!currentCamera) currentCamera = this;

	this->fov			= _radians;
	this->nearPlane		= _near;
	this->farPlane		= _far;

	projection.SetProjection(_radians, (float)WindowManager::GetInstance()->width, (float)WindowManager::GetInstance()->height, _near, _far);
}

void
Camera::UpdateProjection() 
{
	projection.SetProjection(fov, (float)WindowManager::GetInstance()->width, (float)WindowManager::GetInstance()->height, nearPlane, farPlane);
}