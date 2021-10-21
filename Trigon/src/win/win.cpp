#include "win.h"

#include <vector>
#include <iostream>
#include <unordered_set>
///////////////////////////////////////////////////////////////////////////////


bool                initialized     = false;

GLFWwindow*         window          = nullptr;
int                 winWidth        = 800;
int                 winHeight       = 600;
int                 winSamples      = 16;
const char*         winName         = "Window";
bool                winTitleBar     = true;
win::graphicsAPI    winAPI          = win::graphicsAPI::Vulkan;
win::mode           winMode         = win::mode::windowed;
win::winCB          callback        = nullptr;

///////////////////////////////////////////////////////////////////////////////

void resizeCB(GLFWwindow* win, int width, int height)
{
    winWidth    = width;
    winHeight   = height;
    if(callback) callback(width,height);
}

void loadGLFW()
{
    if(!initialized)
    {
        glfwInit();
        initialized = true;
    }
}

void bindGlContext()
{
    glfwWindowHint(GLFW_SAMPLES, winSamples);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    #ifdef _DEBUG
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true); 
    #endif
}

void bindVkContext()
{
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
}

void bindGlesContext()
{

}

///////////////////////////////////////////////////////////////////////////////


void win::createWin()
{
    loadGLFW();
    if(window) glfwDestroyWindow(window);

    switch(winAPI)
    {
        case graphicsAPI::Vulkan:
        bindVkContext();
        break;
        case graphicsAPI::OpenGL:
        bindGlContext();
        break;
        case graphicsAPI::OpenGLES:
        bindVkContext();
        break;
    }

    switch(winMode)
    {
        case mode::windowed:
        window = glfwCreateWindow(winWidth,winHeight,winName, NULL,NULL);
        break;

        case mode::fullscreen:
        window = glfwCreateWindow(winWidth,winHeight,winName,glfwGetPrimaryMonitor(),NULL);
        break;

        case mode::borderless:
        const GLFWvidmode* fcMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        glfwWindowHint(GLFW_RED_BITS, fcMode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, fcMode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, fcMode->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, fcMode->refreshRate);   
        window = glfwCreateWindow(fcMode->width, fcMode->height, winName, glfwGetPrimaryMonitor(), NULL);
        break;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, resizeCB);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);

}

void win::destroyWin()
{
    glfwDestroyWindow(window);
    window = nullptr;
}

void win::release()
{
    if(window)
    {
        glfwDestroyWindow(window);
        window = nullptr; 
    } 

    if(initialized)
    {
        glfwTerminate();
        initialized = false;
    }
}

void win::setName(const char* name)
{
    winName = name;
}

void win::poll()
{
    glfwPollEvents();
}

void win::swap()
{
    glfwSwapBuffers(window);
}

void win::setSize(int width, int height)
{
    winWidth    = width;
    winHeight   = height;
}

void win::setCallback(winCB cb)
{
    callback = cb;
}

void win::setMode(mode m)
{
    winMode = m;
}

void win::setGraphicsAPI(graphicsAPI api)
{
    winAPI = api;
}

bool win::shouldQuit()
{
    return glfwWindowShouldClose(window);
}

void win::setWinSamples(int samples)
{
    winSamples = samples;
}

void win::recreateWin()
{
    destroyWin();
    createWin();
}

std::vector<const char *> win::getRequiredExtensions() 
{
  uint32_t glfwExtensionCount = 0;
  const char **glfwExtensions;
  glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

  std::vector<const char *> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

  #ifdef _DEBUG
extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
  #endif

  return extensions;
}

void win::getVkExtensions() 
{
  uint32_t extensionCount = 0;
  vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
  std::vector<VkExtensionProperties> extensions(extensionCount);
  vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

  std::cout << "available extensions:" << std::endl;
  std::unordered_set<std::string> available;
  for (const auto &extension : extensions) {
    std::cout << "\t" << extension.extensionName << std::endl;
    available.insert(extension.extensionName);
  }

  std::cout << "required extensions:" << std::endl;
  auto requiredExtensions = getRequiredExtensions();
  for (const auto &required : requiredExtensions) {
    std::cout << "\t" << required << std::endl;
    if (available.find(required) == available.end()) {
      throw std::runtime_error("Missing required glfw extension");
    }
  }
}

GLFWwindow* win::getHandle(){return window;}

void win::createSurface(VkInstance instance, VkSurfaceKHR* surface)
{
    if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS) 
    {
    throw std::runtime_error("failed to create window surface!");
  }
}

bool win::isOk()
{
    if(!initialized)    return false;
    if(!window)         return false;
    return true;
}