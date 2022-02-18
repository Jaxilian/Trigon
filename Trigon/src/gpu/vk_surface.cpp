#include "gpu.h"
#ifdef _DEBUG
#include <iostream>
#endif
static VkSurfaceKHR surface;


void vk_surface::create(GLFWwindow* window) 
{
	if (glfwCreateWindowSurface(vk_instance::get(), window, nullptr, &surface) != VK_SUCCESS) 
	{
	#ifdef _DEBUG
			throw std::runtime_error("failed to create a surface!");
	#else
			exit(-1);
	#endif
	}
}

VkSurfaceKHR& vk_surface::get() 
{
	return surface;
}

void vk_surface::destroy() 
{
	if(vk_instance::get() != VK_NULL_HANDLE) vkDestroySurfaceKHR(vk_instance::get(), surface, nullptr);
}