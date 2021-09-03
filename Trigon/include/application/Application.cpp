#include "Application.h"


Application::Application()
{

}

void
Application::BaseSetup()
{
	Debug::Log("\nBase Setup\n");
}

void
Application::OnInit()
{
	Debug::Log("\nEntering On Init\n");


}

void
Application::OnAwake()
{
	Debug::Log("\nEntering On Awake\n");
}

void
Application::OnStart()
{
	Debug::Log("\nEntering On Start\n");

	Debug::Log("\nEntering On Game Loop\n");
}

void
Application::OnEarlyUpdate()
{

}

void
Application::OnUpdate()
{

}

void
Application::OnLateUpdate()
{
	
}

void
Application::OnQuit()
{
	Debug::Log("\nOn Quit\n");


}

bool
Application::ShouldQuit()
{
	if (overrideQuit) return true;
	return appShouldQuit;
}

void
Application::Quit()
{
	overrideQuit = true;
}
