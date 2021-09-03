#include "Matrix4.h"
#include <stdio.h>
#include <math.h>

Matrix4::Matrix4()
{
	eular = Vector3(0, 0, 0);
};

void
Matrix4::QuickPrint()
{
	for(int y = 0; y < 4; y++)
	{
		
		printf("{ %f, %f, %f, %f }\n", data[y][0], data[y][1], data[y][2], data[y][3]);
		
	}
	printf("\n");
}

void
Matrix4::SetProjection(float fov, float aspect, float near, float far)
{
	float tanFOV		= tan(fov / 2);
	float frustumLength = far - near;

	data[0][0] = 1.0f / (tanFOV * aspect);
	data[1][1] = 1.0f / tanFOV;
	data[2][2] = -(far + near) / (far - near);
	data[3][2] =  -1;
	data[2][3] = -(2 * far * near) / (far - near);
}

void
Matrix4::OrthoNormalize()
{

	Vector3 worldUp		= Vector3(0, 1, 0).Normalize();
	Vector3 forward		= GetForward().Normalize();
	Vector3 right		= Vector3::Cross(	forward, worldUp	).Normalize();
	Vector3 up			= Vector3::Cross(	right,	forward		).Normalize();


	SetForward	(-forward);
	SetRight	(right);
	SetUp		(up);

	data[0][3] = -Vector3::Dot(right,	 GetPosition());
	data[1][3] = -Vector3::Dot(up,		 GetPosition());
	data[2][3] = -Vector3::Dot(forward,  GetPosition());

}

void 
Matrix4::LookAt(const Vector3& target)
{
	Vector3 direction = const_cast<Vector3&>(target) - GetPosition();
	SetForward(direction);
	OrthoNormalize();
	pos = GetPosition();
	SetPosition(Vector3(0, 0, 0));
	eular = GetEularAngles();
}

Vector3
Matrix4::GetForward()
{
	Vector3 vec;
	vec.x = data[2][0];
	vec.y = data[2][1];
	vec.z = data[2][2];
	return vec;
}

Vector3
Matrix4::GetUp() 
{
	Vector3 vec;
	vec.x = data[1][0];
	vec.y = data[1][1];
	vec.z = data[1][2];
	return vec;
}

Vector3
Matrix4::GetRight() 
{
	Vector3 vec;
	vec.x = data[0][0];
	vec.y = data[0][1];
	vec.z = data[0][2];
	return vec;
}

Vector3
Matrix4::GetPosition()
{

	pos.x = data[3][0];
	pos.y = data[3][1];
	pos.z = data[3][2];
	return pos;
}

Vector3
Matrix4::GetScale() 
{
	Vector3 scale;

	scale.x = data[0][0];
	scale.y = data[1][1];
	scale.z = data[2][2];

	return scale;
}

void
Matrix4::SetForward(const Vector3& direction)
{
	data[2][0] = direction.x;
	data[2][1] = direction.y;
	data[2][2] = direction.z;
}

void 
Matrix4::SetUp(const Vector3& direction)
{
	data[1][0] = direction.x;
	data[1][1] = direction.y;
	data[1][2] = direction.z;

}

void 
Matrix4::SetRight(const Vector3& direction)
{
	data[0][0] = direction.x;
	data[0][1] = direction.y;
	data[0][2] = direction.z;
}

void
Matrix4::SetPosition(const Vector3& position) 
{
	data[3][0] = position.x;
	data[3][1] = position.y;
	data[3][2] = position.z;
}

void	
Matrix4::SetRotateEular(const Vector3& rotation)
{
	eular = rotation;
	data[1][1] = cos(eular.x);
	data[1][2] = -sin(eular.x);
	data[2][1] = sin(eular.x);
	data[2][2] = cos(eular.x);

	data[0][0] = cos(eular.y);
	data[0][2] = sin(eular.y);
	data[2][0] = -sin(eular.y);
	data[2][2] = cos(eular.y);

	data[0][0] = cos(eular.z);
	data[0][1] = -sin(eular.z);
	data[1][0] = sin(eular.z);
	data[1][1] = cos(eular.z);

	OrthoNormalize();

}

void	
Matrix4::RotateEular(const Vector3& rotation)
{
	eular += rotation;
	if (eular.y > 360) eular.y = 0;
	if (eular.y < 0) eular.y = 360;


	data[1][1] = cos(eular.x);
	data[1][2] = -sin(eular.x);
	data[2][1] = sin(eular.x);
	data[2][2] = cos(eular.x);

	data[0][0] = cos(eular.y);
	data[0][2] = sin(eular.y);
	data[2][0] = -sin(eular.y);
	data[2][2] = cos(eular.y);

	data[0][0] = cos(eular.z);
	data[0][1] = -sin(eular.z);
	data[1][0] = sin(eular.z);
	data[1][1] = cos(eular.z);

	OrthoNormalize();
}

void	
SetRotation(const Vector3& angles) 
{
	
}

void 
Matrix4::SetScale(const Vector3& scale)
{
	data[0][0] = scale.x;
	data[1][1] = scale.y;
	data[2][2] = scale.z;
}

Vector3
Matrix4::GetEularAngles() 
{
	return Vector3();
}

Vector3
Matrix4::GetRotation()
{
	if (data[0][0] == 1.0f)
	{
		eular.z = atan2f(data[0][2], data[2][3]);
		eular.y = 0;
		eular.z = 0;

	}
	else if (data[0][0] == -1.0f)
	{
		eular.z = atan2f(data[0][2], data[2][3]);
		eular.y = 0;
		eular.z = 0;
	}
	else
	{

		eular.z = atan2(-data[0][2], data[0][0]);
		eular.y = asin(data[0][1]);
		eular.x = atan2(-data[1][2], data[1][1]);
	}
	return eular;
}