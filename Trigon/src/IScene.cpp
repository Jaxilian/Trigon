#include "Engine/Scenes/IScene.h"
#include "Engine/Entities/CEntity.h"

IScene* IScene::m_pCurrentWorld = nullptr;

IScene* IScene::GetCurrentWorld() 
{
	return m_pCurrentWorld;
}


IScene::IScene() 
{
	m_pEntities		= new std::vector<Entity*>();
}

IScene::~IScene() 
{
	for (int i = 0; i < m_pEntities->size(); i++) 
	{
		delete m_pEntities->at(i);
	}

	delete m_pEntities;
}

void
IScene::SetActiveWorld(IScene* world)
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
IScene::Update( void )
{

	// Update all entities in world
	for (int EntityIndex = 0; EntityIndex < m_pEntities->size(); ++EntityIndex)
	{
		Entity* pEntity = m_pEntities->at(EntityIndex);

		pEntity->Update();
	}
	

}	// */ // Update

Entity*
IScene::CreateEntity(const char* name)
{
	//////////////////////////////////////////////////////////////////////////

	// Create entity

	Entity* Entity;
	Entity = new Entity(name);

	// Add entity to list
	m_pEntities->push_back(Entity);

	return Entity;

}	// */ // CreateEntity