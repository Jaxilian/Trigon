#include "Application.h"
#include "core/WindowManager.h"
#include "Core/Renderer.h"
#include "Editor/EditorGUI.h"
#include "Engine/Materials/DefaultMaterial.h"

EditorGUI* editor;

Application::Application()
{

}

void
Application::BaseSetup()
{
	WindowManager::CreateInstance();
	Renderer::CreateInstance();
	editor = new EditorGUI();
	DefaultMaterial::instance = new DefaultMaterial();
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
	editor->RenderTestWindow();
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
	delete DefaultMaterial::instance;
	delete editor;
	WindowManager::ReleaseInstance();
	Renderer::ReleaseInstance();
}

bool
Application::ShouldQuit()
{
	return appShouldQuit;
}

