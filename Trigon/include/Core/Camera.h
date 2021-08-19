#ifndef CAMERA_H
#define CAMERA_H
#include "Math/Matrix4.h"
class Camera
{
public:
	float nearPlane	= 0;
	float farPlane	= 0;
	float fov		= 0;

	static Camera* currentCamera;

	Matrix4 projection;
	Matrix4 transform;

	Camera(float _radians, float _near, float _far);
	
	void UpdateProjection();
};

#endif // !CAMERA_H


