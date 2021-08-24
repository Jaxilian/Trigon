#include "core/backend/Renderer.h"
#include "core/backend/Debug.h"

Renderer*
Renderer::m_pInstance = nullptr;

void		
Renderer::SetInstance	(	Renderer* instance		) 
{
#ifdef _DEBUG
	if (m_pInstance) Debug::LogError("A new renderer instance was made but one was alredy existing!");
#endif

	m_pInstance = instance;
}


Renderer*	
Renderer::GetInstance	(			void			)
{
	return m_pInstance;
}