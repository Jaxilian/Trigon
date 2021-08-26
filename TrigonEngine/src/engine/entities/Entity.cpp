//////////////////////////////////////////////////////////////////////////////////////////
//  File name: CEntity.cpp                                                              //
//  Created:   2021-02-10 14:54:23                                                      //
//                                                                                      //
//                                                                                      //
//  Copyright (c) 2021 Jax Carls Wattberg                                               //
//                                                                                      //
//////////////////////////////////////////////////////////////////////////////////////////

#include "engine/components/Component.h"
#include "engine/entities/Entity.h"
#include "core/backend/Debug.h"

////////////////////////////// CEntity //////////////////////////////
//                                                                 //
//  Info:														   //
//                                                                 //
//*//////////////////////////////////////////////////////////////////

Entity::Entity(const char* name)
	: Enabled(true)
{
	m_Name = name;
	m_EntityID = "1234"; // <-- Implement ID
#ifdef _DEBUG
	Debug::LogStatus(DebugColor::Green, DebugType::Create, DebugResult::Success, "Entity: %s", name);
#endif
}	// */ // CEntity


////////////////////////////// ~CEntity //////////////////////////////
//                                                                  //
//  Info:
//                                                                  //
//*///////////////////////////////////////////////////////////////////
Entity::~Entity( void )
{;
	for (int i = 0; i < m_Components.size(); i++) 
	{
		m_Components.at(i)->Unload();
		delete m_Components.at(i);
	}
#ifdef _DEBUG
	Debug::LogStatus(DebugColor::Green, DebugType::Delete, DebugResult::Success, "Entity: %s", m_Name);
#endif

}	// */ // ~CEntity


////////////////////////////// Update //////////////////////////////
//                                                                //
//  Info:
//                                                                //
//*/////////////////////////////////////////////////////////////////
void
Entity::Update( void )
{
	for (int i = 0; i < m_Components.size(); i++) 
	{
		m_Components.at(i)->Update();
	}

}	// */ // Update


////////////////////////////// AddComponentInternal //////////////////////////////
//                                                                              //
//  Info:
//                                                                              //
//*///////////////////////////////////////////////////////////////////////////////
void
Entity::AddComponentInternal(Component* pComponent)
{
	pComponent->m_pEntity = this;
	pComponent->Load();
	// Add the component to our list
	m_Components.push_back(pComponent);

}	// */ // AddComponentInternal