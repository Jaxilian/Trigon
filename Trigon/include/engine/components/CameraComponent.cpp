#include "engine/components/CameraComponent.h"
#include "engine/entities/Entity.h"
#include "engine/components/TransformComponent.h"

CameraComponent* CameraComponent::activeCamera = nullptr;

CameraComponent::CameraComponent()
{
	transform		= nullptr;
	activeCamera	= this;
}

CameraComponent::~CameraComponent()
{

}

void
CameraComponent::Load(void)
{
	transform = &const_cast<TransformComponent*>(GetParent()->GetComponent<TransformComponent>())->matrix;
}

void
CameraComponent::Unload(void)
{
	
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

void 
CameraComponent::SetProjection(float fov, float aspect, float near, float far)
{
	projection.SetProjection(fov, aspect, near, far);
}

Matrix4&
CameraComponent::GetTransformMatrix()
{
	if (GetParent()->GetComponent<TransformComponent>())
	{
		return const_cast<TransformComponent*>(GetParent()->GetComponent<TransformComponent>())->matrix;
	}
}