#ifndef IWorld_H
#define IWorld_H
#pragma once
#include <vector>

class		CEntity;
class		IComponent;

class IWorld
{
private:
	static	IWorld*			m_pCurrentWorld;
	const	char*			m_Name;

	std::vector<CEntity*>*			m_pEntities		= nullptr;

//////////////////////////////////////////////////////////////////////////

public:

	CEntity*	CreateEntity	( const char* name	);
	void		Update			( void );

//////////////////////////////////////////////////////////////////////////
	static IWorld*					GetCurrentWorld();
	static void						SetActiveWorld(IWorld* world);

	IWorld();
	~IWorld();

//////////////////////////////////////////////////////////////////////////
};
#endif // !WorldMaster_h


