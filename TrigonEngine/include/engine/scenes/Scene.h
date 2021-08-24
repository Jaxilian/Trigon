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

	Entity*	CreateEntity	( const char* name	);
	void		Update			( void );

//////////////////////////////////////////////////////////////////////////
	static Scene*					GetCurrentWorld();
	static void						SetActiveWorld(Scene* world);

	Scene();
	~Scene();

//////////////////////////////////////////////////////////////////////////
};
#endif // !WorldMaster_h


