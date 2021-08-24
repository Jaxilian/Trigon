//////////////////////////////////////////////////////////////////////////////////////////
//  File name: CEntity.cpp                                                              //
//  Created:   2021-02-10 14:54:23                                                      //
//                                                                                      //
//                                                                                      //
//  Copyright (c) 2021 Jax Carls Wattberg                                               //
//                                                                                      //
//////////////////////////////////////////////////////////////////////////////////////////

#include "Engine/Components/IComponent.h"
#include "Engine/Entities/CEntity.h"


////////////////////////////// CEntity //////////////////////////////
//                                                                 //
//  Info:														   //
//                                                                 //
//*//////////////////////////////////////////////////////////////////

CEntity::CEntity( const char* name )
	: Enabled(true)
{
	m_Name = name;

}	// */ // CEntity


////////////////////////////// ~CEntity //////////////////////////////
//                                                                  //
//  Info:
//                                                                  //
//*///////////////////////////////////////////////////////////////////
CEntity::~CEntity( void )
{;
	for (int i = 0; i < m_Components.size(); i++) 
	{
		m_Components.at(i)->Unload();
		delete m_Components.at(i);
	}

}	// */ // ~CEntity


////////////////////////////// Update //////////////////////////////
//                                                                //
//  Info:
//                                                                //
//*/////////////////////////////////////////////////////////////////
void
CEntity::Update( void )
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
CEntity::AddComponentInternal(IComponent* pComponent)
{
	pComponent->m_pEntity = this;
	pComponent->Load();
	// Add the component to our list
	m_Components.push_back(pComponent);

}	// */ // AddComponentInternal
