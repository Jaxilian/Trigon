#ifndef IWorld_H
#define IWorld_H
#pragma once
#include <vector>

class		Entity;
class		Component;

class IScene
{
private:
	static	IScene*					m_pCurrentWorld;
	const	char*					m_Name;

	std::vector<Entity*>*			m_pEntities		= nullptr;

//////////////////////////////////////////////////////////////////////////

public:

	Entity*	CreateEntity	( const char* name	);
	void		Update			( void );

//////////////////////////////////////////////////////////////////////////
	static IScene*					GetCurrentWorld();
	static void						SetActiveWorld(IScene* world);

	IScene();
	~IScene();

//////////////////////////////////////////////////////////////////////////
};
#endif // !WorldMaster_h


