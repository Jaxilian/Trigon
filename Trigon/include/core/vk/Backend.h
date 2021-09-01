#ifndef BACKEND_H
#define BACKEND_H

#ifdef _WIN32
#include <Windows.h>
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_EXPOSE_NATIVE_WIN32
#endif // _WIN32

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#define VK_NO_PROTOTYPES
#define VK_USE_PLATFORM_GLFW_KHR
#include <vulkan/vulkan.h>
#include "../Debug.h"


#endif // !BACKEND_H
