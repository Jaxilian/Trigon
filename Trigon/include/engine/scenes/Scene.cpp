#include "engine/scenes/Scene.h"
#include "engine/entities/Entity.h"
#include "core/system/Debug.h"
#include "engine/components/ModelComponent.h"
#include "engine/materials/DefaultMaterial.h"
#include "engine/components/TransformComponent.h"
#include "engine/components/CameraComponent.h"

Scene* Scene::m_pCurrentScene = nullptr;

Scene* Scene::GetCurrentScene() 
{
	return m_pCurrentScene;
}


Scene::Scene(const char* name)
{
	m_Name			= name;
	m_pEntities		= new std::vector<Entity*>();

#ifdef _DEBUG
	Debug::LogStatus(DebugColor::Green, DebugType::Create, DebugResult::Success, "Scene: %s", name);
#endif
}

Scene::~Scene()
{
	for (int i = 0; i < m_pEntities->size(); i++) 
	{
		delete m_pEntities->at(i);
	}

	delete m_pEntities;

#ifdef _DEBUG
	Debug::LogStatus(DebugColor::Green, DebugType::Delete, DebugResult::Success, "Scene: %s", m_Name);
#endif
}

void							
Scene::SetDirectionLightSource(DirectionLightComponent* component) 
{
	m_DirectionalLight = component;
}

DirectionLightComponent*
Scene::GetDirectionalLight()
{
	return m_DirectionalLight;
}

void
Scene::SetActiveScene(Scene* world)
{
	if (m_pCurrentScene) delete m_pCurrentScene;
	m_pCurrentScene = world;
}


unsigned int
Scene::EntityCount() 
{
	return m_pEntities->size();
}

Entity* 
Scene::GetEntity(int index)
{
	return m_pEntities->at(index);
}

const char*
Scene::GetName()
{
	return m_Name;
}


void
Scene::Draw() 
{
	for (int EntityIndex = 0; EntityIndex < m_pEntities->size(); ++EntityIndex)
	{
		Entity*				pEntity		= m_pEntities->at(EntityIndex);

		if (pEntity->Enabled) 
		{
			ModelComponent*		pComponent	= const_cast<ModelComponent*>(pEntity->GetComponent<ModelComponent>());
			if (pComponent && CameraComponent::activeCamera)
			{
				pComponent->model->material->UpdateMatrices
				(
					&pComponent->GetParent()->transform->matrix,
					CameraComponent::activeCamera->transform,
					&CameraComponent::activeCamera->projection
				);

				pComponent->Draw();
			}
		}
	}
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