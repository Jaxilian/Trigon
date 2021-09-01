#include "WindowManager.h"

WindowPtr*  WindowManager::ptr = nullptr;
bool		WindowManager::initialized = false;

WindowPtr*
WindowManager::GetInstance()
{
#ifdef _DEBUG
	if (ptr == nullptr) Debug::LogError("Window pointer is null, have you created a instance?");
#endif // !_DEBUG

	return ptr;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	WindowManager::GetInstance()->m_Width = width;
	WindowManager::GetInstance()->m_Height = height;
	//glViewport(0, 0, width, height);
	//if (Camera::currentCamera) Camera::currentCamera->UpdateProjection();
}

bool
WindowManager::CreateInstance()
{
	if (initialized)
	{
#ifdef _DEBUG
		Debug::LogError("Window instance already initialized!");
#endif
		return false;
	}

	if (!glfwInit())
	{
		Debug::LogStatus(DebugType::Init, DebugResult::Failed, DebugColor::Red, "GLFW");
		return false;
	}

	ptr = new WindowPtr();

	Debug::LogStatus(DebugType::Init, DebugResult::Success, DebugColor::Green, "GLFW");

	ptr->m_Width = 800;
	ptr->m_Height = 600;
	ptr->m_pName = "Trigon";

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	ptr->m_pWindow = glfwCreateWindow(ptr->m_Width, ptr->m_Height, ptr->m_pName, NULL, NULL);

	if (ptr->m_pWindow == NULL)
	{
#ifdef _DEBUG
		Debug::LogStatus(DebugType::Create, DebugResult::Failed, DebugColor::Red, "WindowManager");
#endif

		return false;
	}

	glfwMakeContextCurrent(ptr->m_pWindow);

	glfwSetFramebufferSizeCallback(ptr->m_pWindow, framebuffer_size_callback);

	Debug::LogStatus( DebugType::Create, DebugResult::Success, DebugColor::Green, "WindowManager");

	glfwSetInputMode(ptr->m_pWindow, GLFW_STICKY_KEYS, GLFW_TRUE);

#ifdef _DEBUG
	Debug::LogStatus( DebugType::Create, DebugResult::Success, DebugColor::Green, "Window");
#endif
	return true;
}

bool
WindowManager::ReleaseInstance()
{
	if (!ptr)return true;

	if (ptr->m_pWindow) 
	{
		glfwDestroyWindow(ptr->m_pWindow);
#ifdef _DEBUG
		Debug::LogStatus( DebugType::Release, DebugResult::Success, DebugColor::Green, "Window");
#endif
	}
	delete ptr;
	glfwTerminate();
	Debug::LogStatus(DebugType::Release, DebugResult::Success, DebugColor::Green, "WindowManager");

#ifdef _DEBUG
	Debug::LogStatus( DebugType::Release, DebugResult::Success, DebugColor::Green, "GLFW");
#endif
	return true;
}