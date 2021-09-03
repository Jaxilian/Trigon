#include "Application.h"
#include "core/system/RendererGL.h"
#include "core/system/WindowManager.h"
#include "engine/scenes/Scene.h"
#include "core/system/Time.h"
#include "editor/Editor.h"

Application::Application()
{
	WindowManager::CreateInstance();
	m_pRenderer = new RendererGL();
	m_pRenderer->CreateInstance();
	m_pEditor = new Editor();
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

	if (m_pEditor)
	{
		m_pEditor->Draw();
	}

	glfwSwapBuffers(WindowManager::GetInstance()->m_pWindow);
	glfwPollEvents();
	appShouldQuit = glfwWindowShouldClose(WindowManager::GetInstance()->m_pWindow);
	Time::Update();
}

void
Application::OnQuit()
{
	Debug::Log("\nOn Quit\n");

	if(m_pEditor) delete m_pEditor;
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
