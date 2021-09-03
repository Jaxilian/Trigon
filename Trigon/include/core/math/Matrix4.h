#ifndef MATRIX4_H
#define MATRIX4_H
#include "Vector3.h"

class Matrix4
{
private:
	Vector3 pos;
	Vector3 eular;
	Vector3 scale;

public:

	float data[4][4]
	{
		{ 1.0f, 0.0f, 0.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f, 0.0f },      
		{ 0.0f, 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f }
	};


	float* operator [] (const int& rhs) 
	{
		return data[rhs];
	}

	Matrix4 operator * (const Matrix4& rhs)
	{
		Matrix4 newMat;
							// row			// column		//row		//column			//row		//column		/row			//column
		newMat.data[0][0] = data[0][0] * rhs.data[0][0] + data[0][1] * rhs.data[1][0] + data[0][2] * rhs.data[2][0] + data[0][3] * rhs.data[3][0];
		newMat.data[0][1] = data[0][0] * rhs.data[0][1] + data[0][1] * rhs.data[1][1] + data[0][2] * rhs.data[2][1] + data[0][3] * rhs.data[3][1];
		newMat.data[0][2] = data[0][0] * rhs.data[0][2] + data[0][1] * rhs.data[1][2] + data[0][2] * rhs.data[2][2] + data[0][3] * rhs.data[3][2];
		newMat.data[0][3] = data[0][0] * rhs.data[0][3] + data[0][1] * rhs.data[1][3] + data[0][2] * rhs.data[2][3] + data[0][3] * rhs.data[3][3];

							// row			// column		//row		//column			//row		//column		/row			//column
		newMat.data[1][0] = data[1][0] * rhs.data[0][0] + data[1][1] * rhs.data[1][0] + data[1][2] * rhs.data[2][0] + data[1][3] * rhs.data[3][0];
		newMat.data[1][1] = data[1][0] * rhs.data[0][1] + data[1][1] * rhs.data[1][1] + data[1][2] * rhs.data[2][1] + data[1][3] * rhs.data[3][1];
		newMat.data[1][2] = data[1][0] * rhs.data[0][2] + data[1][1] * rhs.data[1][2] + data[1][2] * rhs.data[2][2] + data[1][3] * rhs.data[3][2];
		newMat.data[1][3] = data[1][0] * rhs.data[0][3] + data[1][1] * rhs.data[1][3] + data[1][2] * rhs.data[2][3] + data[1][3] * rhs.data[3][3];

							// row			// column		//row		//column			//row		//column		/row			//column
		newMat.data[2][0] = data[2][0] * rhs.data[0][0] + data[2][1] * rhs.data[1][0] + data[2][2] * rhs.data[2][0] + data[2][3] * rhs.data[3][0];
		newMat.data[2][1] = data[2][0] * rhs.data[0][1] + data[2][1] * rhs.data[1][1] + data[2][2] * rhs.data[2][1] + data[2][3] * rhs.data[3][1];
		newMat.data[2][2] = data[2][0] * rhs.data[0][2] + data[2][1] * rhs.data[1][2] + data[2][2] * rhs.data[2][2] + data[2][3] * rhs.data[3][2];
		newMat.data[2][3] = data[2][0] * rhs.data[0][3] + data[2][1] * rhs.data[1][3] + data[2][2] * rhs.data[2][3] + data[2][3] * rhs.data[3][3];

							// row			// column		//row		//column			//row		//column		/row			//column
		newMat.data[3][0] = data[3][0] * rhs.data[0][0] + data[3][1] * rhs.data[1][0] + data[3][2] * rhs.data[2][0] + data[3][3] * rhs.data[3][0];
		newMat.data[3][1] = data[3][0] * rhs.data[0][1] + data[3][1] * rhs.data[1][1] + data[3][2] * rhs.data[2][1] + data[3][3] * rhs.data[3][1];
		newMat.data[3][2] = data[3][0] * rhs.data[0][2] + data[3][1] * rhs.data[1][2] + data[3][2] * rhs.data[2][2] + data[3][3] * rhs.data[3][2];
		newMat.data[3][3] = data[3][0] * rhs.data[0][3] + data[3][1] * rhs.data[1][3] + data[3][2] * rhs.data[2][3] + data[3][3] * rhs.data[3][3];

		return newMat;
	}

	void OrthoNormalize();

	void SetProjection(float fov, float aspect, float near, float far);

	void LookAt(const Vector3& target);

	Matrix4();

	void QuickPrint();

	Vector3 GetForward();
	Vector3 GetUp();
	Vector3 GetRight();
	Vector3 GetPosition();
	Vector3 GetScale();

	void	SetForward(const Vector3& direction);
	void	SetUp(const Vector3& direction);
	void	SetRight(const Vector3& direction);
	void	SetPosition(const Vector3& position);
	void	SetRotateEular(const Vector3& rotation);
	void	RotateEular(const Vector3& rotation);
	Vector3	GetRotation();
	//void	SetRotation(const Vector3& angles);
	void	SetScale(const Vector3& scale);
	Vector3 GetEularAngles();

};

#endif // !MATRIX4_H
