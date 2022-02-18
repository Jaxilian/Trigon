#include "Application.h"

extern Application* startApplication();

#ifdef _DEBUG
int main()
{
	auto app = startApplication();

	app->Load();
	app->Init();
	app->OnConstruct();
	app->OnStart();

	unsigned int winId = app->GetMainWindow();


	app->OnQuit();


	delete app;
	return 0;
}
#else
#ifdef _WIN32
#include <Windows.h>
	int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PSTR szCmdLine, _In_ int iCmdShow)
	{
		auto app = startApplication();

		app->Load();
		app->Init();
		app->OnConstruct();
		app->OnStart();

		unsigned int winId = app->GetMainWindow();


		app->OnQuit();


		delete app;
		return 0;
	}
#else
#endif


#endif