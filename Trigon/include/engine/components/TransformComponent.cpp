#include "engine/components/TransformComponent.h"
#include "engine/entities/Entity.h"
#include "core/system/Debug.h"
#include "core/math/Vector3.h"

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
	
	return Vector3();
}	// */ // Update

////////////////////////////// Get Pos //////////////////////////////
//                                                                //
//  Info:
//                                                                //
//*/////////////////////////////////////////////////////////////////
Vector3
TransformComponent::GetScale(void)
{
	
	return Vector3();
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

}

////////////////////////////  Look  ////////////////////////////////
//                                                                //
//  Info:
//                                                                //
//*/////////////////////////////////////////////////////////////////

void
TransformComponent::LookAt(Vector3 target, Vector3 up)
{
	

}

///////////////////////////  Apply  ////////////////////////////////
//                                                                //
//  Info:
//                                                                //
//*/////////////////////////////////////////////////////////////////

void
TransformComponent::ApplyChanges()
{
	
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
	
}

void TransformComponent::SetPosition(Vector3 position)
{

}

