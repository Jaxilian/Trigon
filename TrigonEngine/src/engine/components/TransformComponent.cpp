#include "engine/components/TransformComponent.h"
#include "engine/entities/Entity.h"
#include "core/backend/Debug.h"


//////////////////////// TransformComponent ////////////////////////////
//                                                                    //
//  Info:
//                                                                    //
//*/////////////////////////////////////////////////////////////////////
TransformComponent::TransformComponent(void)
{
	
}	// */ // IComponent


////////////////////////// ~TransformComponent //////////////////////////
//                                                                     //
//  Info:
//                                                                     //
//*//////////////////////////////////////////////////////////////////////
TransformComponent::~TransformComponent(void)
{

}	// */ // ~IComponent


////////////////////////////// Load //////////////////////////////
//                                                              //
//  Info:
//                                                              //
//*///////////////////////////////////////////////////////////////
void
TransformComponent::Load(void)
{
	matrix = new Matrix4();

	if (m_pEntity->transform != nullptr)
	{
		Debug::LogError("%s already has a transform!", m_pEntity->GetName());
		return;
	}

	m_pEntity->transform = this;
}	// */ // OnLoad


////////////////////////////// Unload //////////////////////////////
//                                                                //
//  Info:
//                                                                //
//*/////////////////////////////////////////////////////////////////
void
TransformComponent::Unload(void)
{
	delete matrix;
}	// */ // Unload


////////////////////////////// Update //////////////////////////////
//                                                                //
//  Info:
//                                                                //
//*/////////////////////////////////////////////////////////////////
void
TransformComponent::Update(void)
{
	ApplyChanges();
}	// */ // Update


////////////////////////////// Get Pos //////////////////////////////
//                                                                //
//  Info:
//                                                                //
//*/////////////////////////////////////////////////////////////////
Vector3
TransformComponent::GetPosition(void)
{
	return matrix->position;
}	// */ // Update

////////////////////////////// Get Pos //////////////////////////////
//                                                                //
//  Info:
//                                                                //
//*/////////////////////////////////////////////////////////////////
Vector3
TransformComponent::GetScale(void)
{
	return matrix->scale;
}	// */ // Update

/////////////////////////// Get Matrix /////////////////////////////
//                                                                //
//  Info:
//                                                                //
//*/////////////////////////////////////////////////////////////////
Matrix4&
TransformComponent::GetMatrix(void)
{
	return *matrix;
}	// */ // Update


///////////////////////////// Scale	 ///////////////////////////////
//                                                                //
//  Info:
//                                                                //
//*/////////////////////////////////////////////////////////////////

void
TransformComponent::Scale(Vector3 value)
{

}

///////////////////////////	 Translate //////////////////////////////
//                                                                //
//  Info:
//                                                                //
//*/////////////////////////////////////////////////////////////////

void
TransformComponent::Translate(Vector3 position)
{
	matrix->Translate(position);
}

////////////////////////////  Look  ////////////////////////////////
//                                                                //
//  Info:
//                                                                //
//*/////////////////////////////////////////////////////////////////

void
TransformComponent::LookAt(Vector3 target, Vector3 up)
{
	matrix->LookAt(target, up);
}

///////////////////////////  Apply  ////////////////////////////////
//                                                                //
//  Info:
//                                                                //
//*/////////////////////////////////////////////////////////////////

void
TransformComponent::ApplyChanges()
{

	matrix->ApplyChanges();
}

///////////////////////////  Rotate  ////////////////////////////////
//                                                                //
//  Info:
//                                                                //
//*/////////////////////////////////////////////////////////////////

void TransformComponent::SetRotation(Vector3 orientation)
{
	//matrix.rotation = orientation;
}

void
TransformComponent::Rotate(Vector3 rotation)
{
	matrix->Rotate(rotation);

}

void TransformComponent::SetPosition(Vector3 position)
{
	matrix->SetPosition(position);
}

