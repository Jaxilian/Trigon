#ifndef GAME_H
#define GAME_H
/*
#include "application/Application.h"
#include "Trigon.h"

class Game : public Application
{
private:
	Scene* scene;
	Entity* camera;
	Entity* model;

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

*/

#include "core\Renderer.h"

int main() 
{
	Renderer::CreateInstance();

	Renderer::DestroyInstance();
	return 0;
}

#endif // !GAME_H
