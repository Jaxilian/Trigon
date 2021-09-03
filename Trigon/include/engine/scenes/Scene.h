#ifndef IWorld_H
#define IWorld_H
#pragma once
#include <vector>

class		Entity;
class		Component;
class		DirectionLightComponent;

class Scene
{
private:
	static	Scene*					m_pCurrentScene;
	const	char*					m_Name;
	DirectionLightComponent*		m_DirectionalLight;
	std::vector<Entity*>*			m_pEntities		= nullptr;

//////////////////////////////////////////////////////////////////////////

public:

	Entity*		CreateEntity	( const char* name	);
	void		Update			( void );
	void		Draw			( void );

//////////////////////////////////////////////////////////////////////////
	static Scene*					GetCurrentScene();
	static void						SetActiveScene(Scene* world);
	void							SetDirectionLightSource(DirectionLightComponent* component);

	unsigned int					EntityCount();
	Entity*							GetEntity(int index);
	DirectionLightComponent*		GetDirectionalLight();
	const char*						GetName();

	 Scene(const char* name);
	~Scene();

//////////////////////////////////////////////////////////////////////////
};
#endif // !WorldMaster_h


