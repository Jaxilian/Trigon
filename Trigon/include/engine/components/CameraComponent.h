#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H
#include "Component.h"
#include "core\math\Matrix4.h"

class TransformComponent;

class CameraComponent : public Component
{
public:
	static CameraComponent* activeCamera;
	Matrix4  projection;
	Matrix4* transform;

	CameraComponent();
	~CameraComponent();

	//////////////////////////////////////////////////////////////////////////

	virtual void	Load(void) override;
	virtual void	Unload(void) override;
	virtual void	Update(void) override;

	/////////////////////////////////////////////////////////////////////////

	void			SetAsCurrentCamera();
	Matrix4&		GetTransformMatrix();

	
};

#endif // !CAMERACOMPONENT_H
