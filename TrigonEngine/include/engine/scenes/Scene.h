#ifndef IWorld_H
#define IWorld_H
#pragma once
#include <vector>

class		Entity;
class		Component;

class Scene
{
private:
	static	Scene*					m_pCurrentWorld;
	const	char*					m_Name;

	std::vector<Entity*>*			m_pEntities		= nullptr;

//////////////////////////////////////////////////////////////////////////

public:

	Entity*		CreateEntity	( const char* name	);
	void		Update			( void );
	void		Draw			( void );

//////////////////////////////////////////////////////////////////////////
	static Scene*					GetCurrentScene();
	static void						SetActiveScene(Scene* world);

	unsigned int					EntityCount();
	Entity*							GetEntity(int index);
	const char*						GetName();

	 Scene(const char* name);
	~Scene();

//////////////////////////////////////////////////////////////////////////
};
#endif // !WorldMaster_h


