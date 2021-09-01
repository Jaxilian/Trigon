#include "core/backend/Camera.h"
#include "core/backend/WindowManager.h"

Camera* Camera::currentCamera = nullptr;

Camera::Camera(float _radians, float _near, float _far)
{
	if (!currentCamera) currentCamera = this;

	this->fov = _radians;
	this->nearPlane = _near;
	this->farPlane = _far;

	projection.SetProjection(_radians, (float)WindowManager::GetInstance()->m_Width, (float)WindowManager::GetInstance()->m_Height, _near, _far);
}

void
Camera::UpdateProjection()
{
	projection.SetProjection(fov, (float)WindowManager::GetInstance()->m_Width, (float)WindowManager::GetInstance()->m_Height, nearPlane, farPlane);
}