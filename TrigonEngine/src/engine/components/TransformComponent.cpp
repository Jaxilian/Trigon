#include "engine/components/TransformComponent.h"
#include "engine/entities/Entity.h"
#include "core/backend/Debug.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/euler_angles.hpp>
#include "core/math/Vector3.h"

//////////////////////// TransformComponent ////////////////////////////
//                                                                    //
//  Info:
//                                                                    //
//*/////////////////////////////////////////////////////////////////////
TransformComponent::TransformComponent(void)
{
	storedScale = Vector3(1, 1, 1);
	storedPos = Vector3(0, 0, 0);
	storedRot = Vector3(0, 0, 0);
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
	data = glm::mat4(1.0f);

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
	glm::mat4 transposed = glm::transpose(data);
	Vector3 pos;
	pos.x = transposed[3][0];
	pos.y = transposed[3][1];
	pos.z = transposed[3][2];
	return pos;
}	// */ // Update

////////////////////////////// Get Pos //////////////////////////////
//                                                                //
//  Info:
//                                                                //
//*/////////////////////////////////////////////////////////////////
Vector3
TransformComponent::GetScale(void)
{
	glm::mat4 transposed = glm::transpose(data);
	Vector3 scale;
	scale.x = transposed[0][0];
	scale.y = transposed[1][1];
	scale.z = transposed[2][2];
	return scale;
}	// */ // Update

/////////////////////////// Get Matrix /////////////////////////////
//                                                                //
//  Info:
//                                                                //
//*/////////////////////////////////////////////////////////////////
glm::mat4&
TransformComponent::GetMatrix(void)
{
	return data;
}	// */ // Update


///////////////////////////// Scale	 ///////////////////////////////
//                                                                //
//  Info:
//                                                                //
//*/////////////////////////////////////////////////////////////////

void
TransformComponent::Scale(Vector3 value)
{
	storedScale += value;
}

///////////////////////////	 Translate //////////////////////////////
//                                                                //
//  Info:
//                                                                //
//*/////////////////////////////////////////////////////////////////

void
TransformComponent::Translate(Vector3 position)
{
	storedPos += position;
}

////////////////////////////  Look  ////////////////////////////////
//                                                                //
//  Info:
//                                                                //
//*/////////////////////////////////////////////////////////////////

void
TransformComponent::LookAt(Vector3 target, Vector3 up)
{
	data = glm::lookAt(storedPos.data, target.data, up.data);

	glm::mat4 transposed = glm::transpose(data);


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

