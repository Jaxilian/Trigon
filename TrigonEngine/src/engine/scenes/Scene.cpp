#include "engine/scenes/Scene.h"
#include "engine/entities/Entity.h"

Scene* Scene::m_pCurrentWorld = nullptr;

Scene* Scene::GetCurrentWorld() 
{
	return m_pCurrentWorld;
}


Scene::Scene()
{
	m_pEntities		= new std::vector<Entity*>();
}

Scene::~Scene()
{
	for (int i = 0; i < m_pEntities->size(); i++) 
	{
		delete m_pEntities->at(i);
	}

	delete m_pEntities;
}

void
Scene::SetActiveWorld(Scene* world)
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
Scene::Update( void )
{

	// Update all entities in world
	for (int EntityIndex = 0; EntityIndex < m_pEntities->size(); ++EntityIndex)
	{
		Entity* pEntity = m_pEntities->at(EntityIndex);

		pEntity->Update();
	}
	

}	// */ // Update

Entity*
Scene::CreateEntity(const char* name)
{
	//////////////////////////////////////////////////////////////////////////

	// Create entity
	Entity* entity;
	entity = new Entity(name);

	// Add entity to list
	m_pEntities->push_back(entity);

	return entity;

}	// */ // CreateEntity