#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H
#include "Component.h"
#include "core/backend/Camera.h"

class TransformComponent;

class CameraComponent : public Component
{
public:
	static CameraComponent* activeCamera;
	Camera* camera;

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
