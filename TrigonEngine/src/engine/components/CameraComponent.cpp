#include "engine/components/CameraComponent.h"
#include "engine/entities/Entity.h"
#include "engine/components/TransformComponent.h"

CameraComponent* CameraComponent::activeCamera = nullptr;

CameraComponent::CameraComponent()
{
	camera			= new Camera(80.0f, 0.1f, 10000.0f);
	activeCamera	= this;
}

CameraComponent::~CameraComponent()
{

}

void
CameraComponent::Load(void)
{

}

void
CameraComponent::Unload(void)
{
	delete camera;
}

void
CameraComponent::Update(void)
{

}

void
CameraComponent::SetAsCurrentCamera()
{
	activeCamera = this;
}

Matrix4&
CameraComponent::GetTransformMatrix()
{
	if (GetParent()->GetComponent<TransformComponent>())
	{
		return const_cast<TransformComponent*>(GetParent()->GetComponent<TransformComponent>())->GetMatrix();
	}
}