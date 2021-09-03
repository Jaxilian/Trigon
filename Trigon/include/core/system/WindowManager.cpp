#include "WindowManager.h"
//#include "Core/Camera.h"

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
	glViewport(0, 0, width, height);
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
		Debug::LogStatus(DebugColor::Red, DebugType::Init, DebugResult::Failed, "GLFW");
		return false;
	}

	ptr = new WindowPtr();

	Debug::LogStatus(DebugColor::Green, DebugType::Init, DebugResult::Success, "GLFW");

	glfwWindowHint(GLFW_SAMPLES, 16);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	ptr->m_Width = 800;
	ptr->m_Height = 600;
	ptr->m_pName = "DEBUG";

	ptr->m_pWindow = glfwCreateWindow(ptr->m_Width, ptr->m_Height, ptr->m_pName, NULL, NULL);

	if (ptr->m_pWindow == NULL)
	{
#ifdef _DEBUG
		Debug::LogStatus(DebugColor::Red, DebugType::Create, DebugResult::Failed, "Window");
#endif

		return false;
	}

	glfwMakeContextCurrent(ptr->m_pWindow);

	glfwSetFramebufferSizeCallback(ptr->m_pWindow, framebuffer_size_callback);

	Debug::LogStatus(DebugColor::Green, DebugType::Create, DebugResult::Success, "Window");

	glfwSetInputMode(ptr->m_pWindow, GLFW_STICKY_KEYS, GLFW_TRUE);

#ifdef _DEBUG
	Debug::LogStatus(DebugColor::Green, DebugType::Create, DebugResult::Success, "WindowManager");
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
		Debug::LogStatus(DebugColor::Green, DebugType::Delete, DebugResult::Success, "Window");
#endif
	}
	delete ptr;
	glfwTerminate();

#ifdef _DEBUG
	Debug::LogStatus(DebugColor::Green, DebugType::Delete, DebugResult::Success, "WindowManager");
#endif
	return true;
}