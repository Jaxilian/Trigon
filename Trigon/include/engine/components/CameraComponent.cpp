#include "engine/components/CameraComponent.h"
#include "engine/entities/Entity.h"
#include "engine/components/TransformComponent.h"

CameraComponent* CameraComponent::activeCamera = nullptr;

CameraComponent::CameraComponent()
{
	
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
		return const_cast<TransformComponent*>(GetParent()->GetComponent<TransformComponent>())->matrix;
	}
}