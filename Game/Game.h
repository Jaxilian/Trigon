#ifndef GAME_H
#define GAME_H

#include "application/Application.h"
#include "engine/scenes/Scene.h"
#include "engine/entities/Entity.h"
#include "engine/components/TransformComponent.h"
#include "engine/components/CameraComponent.h"
#include "engine/components/ModelComponent.h"
#include "engine/materials/DefaultMaterial.h"

class Game : public Application
{
private:
	Scene*	m_pScene;
	Entity* m_pModel;
	Entity* m_pCamera;

public:

	void OnInit()			override;
	void OnAwake()			override;
	void OnStart()			override;
	void OnEarlyUpdate()	override;
	void OnUpdate()			override;
	void OnLateUpdate()		override;
	void OnQuit()			override;
};



Application* CreateApplication()
{
	return new Game();
}


#endif // !GAME_H
