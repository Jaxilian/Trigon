#include "Application.h"
#include "core/WindowManager.h"
#include "Core/Renderer.h"
#include "Editor/EditorGUI.h"

Application::Application()
{

}

void
Application::BaseSetup()
{
	WindowManager::CreateInstance();
	Renderer::CreateInstance();
	EditorGUI::instance = new EditorGUI();
}

void
Application::OnInit()
{


}

void
Application::OnAwake()
{

}

void
Application::OnStart()
{
	
}

void
Application::OnEarlyUpdate()
{
	Renderer::Clear();
}

void
Application::OnUpdate()
{
	
}

void
Application::OnLateUpdate()
{
	glfwSwapBuffers(WindowManager::GetInstance()->window);
	glfwPollEvents();
	appShouldQuit = glfwWindowShouldClose(WindowManager::GetInstance()->window);
}

void
Application::OnQuit()
{
	delete EditorGUI::instance;
	WindowManager::ReleaseInstance();
	Renderer::ReleaseInstance();
}

bool
Application::ShouldQuit()
{
	return appShouldQuit;
}

