#include "Engine/Scenes/IScene.h"
#include "Engine/Entities/CEntity.h"

IWorld* IWorld::m_pCurrentWorld = nullptr;

IWorld* IWorld::GetCurrentWorld() 
{
	return m_pCurrentWorld;
}


IWorld::IWorld() 
{
	m_pEntities		= new std::vector<CEntity*>();
}

IWorld::~IWorld() 
{
	for (int i = 0; i < m_pEntities->size(); i++) 
	{
		delete m_pEntities->at(i);
	}

	delete m_pEntities;
}

void
IWorld::SetActiveWorld(IWorld* world)
{
	if (m_pCurrentWorld) delete m_pCurrentWorld;
	m_pCurrentWorld = world;
}



////////////////////////////// Update //////////////////////////////
//                                                                //
//  Info:
//                                                                //
//*/////////////////////////////////////////////////////////////////
void
IWorld::Update( void )
{

	// Update all entities in world
	for (int EntityIndex = 0; EntityIndex < m_pEntities->size(); ++EntityIndex)
	{
		CEntity* pEntity = m_pEntities->at(EntityIndex);

		pEntity->Update();
	}
	

}	// */ // Update

CEntity*
IWorld::CreateEntity(const char* name)
{
	//////////////////////////////////////////////////////////////////////////

	// Create entity

	CEntity* Entity;
	Entity = new CEntity(name);

	// Add entity to list
	m_pEntities->push_back(Entity);

	return Entity;

}	// */ // CreateEntity