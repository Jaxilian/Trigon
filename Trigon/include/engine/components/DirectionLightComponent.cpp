#include "engine/components/DirectionLightComponent.h"
#include "engine/components/ModelComponent.h"
#include "engine/scenes/Scene.h"
#include "engine/components/TransformComponent.h"
#include "engine/entities/Entity.h"
#include "core/system/Renderer.h"
#include "engine/scenes/Scene.h"

////////////////////////////// IComponent //////////////////////////////
//                                                                    //
//  Info:
//                                                                    //
//*/////////////////////////////////////////////////////////////////////
DirectionLightComponent::DirectionLightComponent()
{
	direction = Vector3(0, -1, 0);

	if (!Scene::GetCurrentScene()->GetDirectionalLight())
	{
		Scene::GetCurrentScene()->SetDirectionLightSource(this);
	}
}	// */ // IComponent


////////////////////////////// ~IComponent //////////////////////////////
//                                                                     //
//  Info:
//                                                                     //
//*//////////////////////////////////////////////////////////////////////
DirectionLightComponent::~DirectionLightComponent(void)
{

}	// */ // ~IComponent


////////////////////////////// Load //////////////////////////////
//                                                              //
//  Info:
//                                                              //
//*///////////////////////////////////////////////////////////////
void
DirectionLightComponent::Load(void)
{

}	// */ // OnLoad


////////////////////////////// Unload //////////////////////////////
//                                                                //
//  Info:
//                                                                //
//*/////////////////////////////////////////////////////////////////
void
DirectionLightComponent::Unload(void)
{

}	// */ // Unload


////////////////////////////// Update //////////////////////////////
//                                                                //
//  Info:
//                                                                //
//*/////////////////////////////////////////////////////////////////
void
DirectionLightComponent::Update(void)
{

}	// */ // Update
