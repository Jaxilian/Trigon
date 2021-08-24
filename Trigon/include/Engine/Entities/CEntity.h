//////////////////////////////////////////////////////////////////////////////////////////
//  File name: CEntity.h                                                                //
//  Created:   2021-02-10 14:54:23                                                      //
//                                                                                      //
//                                                                                      //
//  Copyright (c) 2021 Jax Carls Wattberg                                               //
//                                                                                      //
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef CEntity_H
#define CEntity_H
#pragma once

class IComponent;
class TransformComponent;
#include <vector>

class CEntity
{
public:

	//////////////////////////////////////////////////////////////////////////

	TransformComponent* transform = nullptr;
	bool				Enabled;

	//////////////////////////////////////////////////////////////////////////

	 CEntity(const char* name);
	~CEntity();

	//////////////////////////////////////////////////////////////////////////

	void		Update	( void );
	const char* GetName() { return m_Name; };

	//////////////////////////////////////////////////////////////////////////

	template< typename T, typename... TArgs >
	T* AddComponent(const TArgs&... rArgs)
	{
		T* pComponent = new T(rArgs...);
		AddComponentInternal(pComponent);
		return pComponent;
	}

	template< typename T >
	const T* GetComponent(void) const
	{
		for (IComponent* pComponent : m_Components)
		{
			if (&typeid(T) == &typeid(*pComponent))
				return static_cast<T*>(pComponent);
		}

		return NULL;
	}

	const char* GetID() {return m_EntityID;}

	//////////////////////////////////////////////////////////////////////////

private:

	void	AddComponentInternal(IComponent* pComponent);

	//////////////////////////////////////////////////////////////////////////

	std::vector< IComponent* >	m_Components;
	const char* m_EntityID;
	const char* m_Name;
};

#endif // !CEntity_H


