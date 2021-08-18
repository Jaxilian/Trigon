#ifndef CAMERA_H
#define CAMERA_H
#include "Math/Matrix4.h"
class Camera
{
public:
	static Camera* currentCamera;

	Matrix4 projection;
	Matrix4 transform;

	Camera();
};

#endif // !CAMERA_H


