#include "Core/Camera.h"
Camera* Camera::currentCamera = nullptr;

Camera::Camera() 
{
	if (!currentCamera) currentCamera = this;
}