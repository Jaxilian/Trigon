#include "application/Application.h"
#include "core/backend/WindowManager.h"
#include "core/backend/RendererGL.h"
#include "core/backend/Time.h"
#include "engine/scenes/Scene.h"

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
	WindowManager::CreateInstance();
	m_pRenderer = new RendererGL();
	m_pRenderer->CreateInstance();
	m_pEditor	= new Editor();

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
	m_pRenderer->ClearViewport();
}

void
Application::OnUpdate()
{
	if (Scene::GetCurrentScene())
	{
		Scene::GetCurrentScene()->Update();
	}
}

void
Application::OnLateUpdate()
{
	if (Scene::GetCurrentScene()) 
	{
		Scene::GetCurrentScene()->Draw();
	}

	m_pEditor->Draw();

	glfwSwapBuffers(WindowManager::GetInstance()->window);
	glfwPollEvents();
	appShouldQuit = glfwWindowShouldClose(WindowManager::GetInstance()->window);
	Time::Update();
}

void
Application::OnQuit()
{
	Debug::Log("\nQuitting\n");

	delete m_pEditor;
	m_pRenderer->ReleaseInstance();
	WindowManager::ReleaseInstance();
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
