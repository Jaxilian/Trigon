//////////////////////////////////////////////////////////////////////////////////////////
//  File name: CEntity.h                                                                //
//  Created:   2021-02-10 14:54:23                                                      //
//                                                                                      //
//                                                                                      //
//  Copyright (c) 2021 Jax Carls Wattberg                                               //
//                                                                                      //
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef Entity_H
#define Entity_H
#pragma once

class Component;
class TransformComponent;
#include <vector>

class Entity
{
private:

	void	AddComponentInternal(Component* pComponent);

	//////////////////////////////////////////////////////////////////////////

	std::vector< Component* >	m_Components;
	const char*					m_EntityID;
	const char*					m_Name;

public:

	//////////////////////////////////////////////////////////////////////////

	TransformComponent* transform = nullptr;
	bool				Enabled;

	//////////////////////////////////////////////////////////////////////////

	 Entity(const char* name);
	~Entity();

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
		for (Component* pComponent : m_Components)
		{
			if (&typeid(T) == &typeid(*pComponent))
				return static_cast<T*>(pComponent);
		}

		return NULL;
	}

	const char* GetID() {return m_EntityID;}

	//////////////////////////////////////////////////////////////////////////

};

#endif // !CEntity_H


