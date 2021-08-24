#include "application/Application.h"
extern Application* CreateApplication();


int main()
{
	auto app = CreateApplication();

	app->BaseSetup();
	app->OnInit();
	app->OnAwake();
	app->OnStart();

	while (!app->ShouldQuit())
	{
		app->OnEarlyUpdate();
		app->OnUpdate();
		app->OnLateUpdate();
	}

	app->OnQuit();

	delete app;

	return 0;
}