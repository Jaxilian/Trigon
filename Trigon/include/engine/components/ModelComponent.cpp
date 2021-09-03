#include "engine/components/ModelComponent.h"
#include "engine/scenes/Scene.h"
#include "engine/components/TransformComponent.h"
#include "engine/entities/Entity.h"
#include "core/system/Renderer.h"

////////////////////////////// IComponent //////////////////////////////
//                                                                    //
//  Info:
//                                                                    //
//*/////////////////////////////////////////////////////////////////////
ModelComponent::ModelComponent(Model* model)
{
	this->model = model;
}	// */ // IComponent


////////////////////////////// ~IComponent //////////////////////////////
//                                                                     //
//  Info:
//                                                                     //
//*//////////////////////////////////////////////////////////////////////
ModelComponent::~ModelComponent(void)
{
	
}	// */ // ~IComponent


////////////////////////////// Load //////////////////////////////
//                                                              //
//  Info:
//                                                              //
//*///////////////////////////////////////////////////////////////
void
ModelComponent::Load(void)
{

}	// */ // OnLoad


////////////////////////////// Unload //////////////////////////////
//                                                                //
//  Info:
//                                                                //
//*/////////////////////////////////////////////////////////////////
void
ModelComponent::Unload(void)
{

}	// */ // Unload


////////////////////////////// Update //////////////////////////////
//                                                                //
//  Info:
//                                                                //
//*/////////////////////////////////////////////////////////////////
void
ModelComponent::Update(void)
{

}	// */ // Update

void
ModelComponent::Draw() 
{
	GetParent()->transform->ApplyChanges();
	Renderer::GetInstance()->Draw(model);
}

