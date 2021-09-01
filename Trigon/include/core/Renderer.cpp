#include "Renderer.h"
#include "WindowManager.h"
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <array>
#include <fstream>

#pragma warning( disable : 26812 )
Renderer*		Renderer::m_pRenderer;

Renderer* 
Renderer::CreateInstance() 
{
#ifdef _WIN32
	if (!LoadLibraryA("vulkan-1.dll"))
	{
		Debug::LogStatus(DebugType::Create, DebugResult::Failed, DebugColor::Red, "Renderer");
		Debug::LogError("Vulkan doesn't exist! Update your graphics driver!");
		return nullptr;
	}
	else 
	{
		Debug::LogStatus(DebugType::Bind, DebugResult::Success, DebugColor::Green, "vulkan-1.dll");
	}
#endif // _WIN32


	if (m_pRenderer)
	{
		Debug::LogStatus(DebugType::Create, DebugResult::Failed, DebugColor::Red, "Renderer");
		Debug::LogError("Renderer Instance already exists!");
		return nullptr;
	}

	m_pRenderer = new Renderer();
	Debug::LogStatus(DebugType::Create, DebugResult::Success, DebugColor::Green, "Renderer");

	WindowManager::CreateInstance();
	
	m_pRenderer->m_pWindow		= WindowManager::GetInstance();
	m_pRenderer->m_pContext		= new vkContext();
	m_pRenderer->m_pSettings	= new vkSettings();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Create vulkan instance

	m_pRenderer->Init();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	return nullptr;
}

Renderer*
Renderer::GetInstance() 
{
	return nullptr;
}

void 
Renderer::DestroyInstance() 
{
	m_pRenderer->CleanupSwapChain();

	vkContext* context = m_pRenderer->m_pContext;

	if(context->descriptorSetLayout) vkDestroyDescriptorSetLayout(context->logicalDevice, context->descriptorSetLayout, nullptr);
	Debug::LogStatus(DebugType::Release, DebugResult::Success, DebugColor::Green, "Descriptor");

	if (context->logicalDevice) vkDestroyDevice(context->logicalDevice, nullptr);
	Debug::LogStatus(DebugType::Release, DebugResult::Success, DebugColor::Green, "Logical Device");

	if(context->debugMessenger)	m_pRenderer->DestroyDebugUtilsMessengerEXT(context->instance, context->debugMessenger, nullptr);
	Debug::LogStatus(DebugType::Release, DebugResult::Success, DebugColor::Green, "DebugMessenger");

	if(context->surface) vkDestroySurfaceKHR(context->instance, context->surface, nullptr);
	Debug::LogStatus(DebugType::Release, DebugResult::Success, DebugColor::Green, "surface");

	if (context->instance) vkDestroyInstance(context->instance, nullptr);
	Debug::LogStatus(DebugType::Release, DebugResult::Success, DebugColor::Green, "vkInstance");

	WindowManager::ReleaseInstance();
	Debug::LogStatus(DebugType::Release, DebugResult::Success, DebugColor::Green, "Renderer");
	


}

void 
Renderer::CleanupSwapChain() 
{
	/*
	vkDestroyImageView(device, depthImageView, nullptr);
	vkDestroyImage(device, depthImage, nullptr);
	vkFreeMemory(device, depthImageMemory, nullptr);

	vkDestroyImageView(device, colorImageView, nullptr);
	vkDestroyImage(device, colorImage, nullptr);
	vkFreeMemory(device, colorImageMemory, nullptr);

	for (auto framebuffer : swapChainFramebuffers) 
	{
		vkDestroyFramebuffer(device, framebuffer, nullptr);
	}

	vkFreeCommandBuffers(device, commandPool, static_cast<uint32_t>(commandBuffers.size()), commandBuffers.data());

	*/
	if(m_pContext->graphicsPipeline)  vkDestroyPipeline(m_pContext->logicalDevice, m_pContext->graphicsPipeline, nullptr);

	if (m_pContext->graphicsPipeline) vkDestroyPipelineLayout(m_pContext->logicalDevice, m_pContext->pipelineLayout, nullptr);

	if (m_pContext->renderPass)vkDestroyRenderPass(m_pContext->logicalDevice, m_pContext->renderPass, nullptr);
	Debug::LogStatus(DebugType::Release, DebugResult::Success, DebugColor::Green, "RenderPass");

	for (auto imageView : m_pContext->swapChainImageViews)
	{
		vkDestroyImageView(m_pContext->logicalDevice, imageView, nullptr);
	}
	Debug::LogStatus(DebugType::Release, DebugResult::Success, DebugColor::Green, "ImageViews");

	if(m_pContext->swapChain)vkDestroySwapchainKHR(m_pContext->logicalDevice, m_pContext->swapChain, nullptr);
	Debug::LogStatus(DebugType::Release, DebugResult::Success, DebugColor::Green, "SwapChain");
	/*
	for (size_t i = 0; i < m_pContext->swapChainImages.size(); i++) {
		vkDestroyBuffer(m_pContext->logicalDevice, uniformBuffers[i], nullptr);
		vkFreeMemory(m_pContext->logicalDevice, uniformBuffersMemory[i], nullptr);
	}
	*/

	//vkDestroyDescriptorPool(m_pContext->logicalDevice, m_pContext->descriptorPool, nullptr);
}

bool
Renderer::Init() 
{

	if (!CreateVkInstance(&m_pContext->instance)) return false;
	Debug::LogStatus(DebugType::Create, DebugResult::Success, DebugColor::Green, "vkInstance");

	SetupDebugMessenger();

	CreateSurface();

	if (!PickPhysicalDevice()) return false;

	if (!CreateLogicalDevice()) return false;

	if (!CreateSwapChain()) return false;

	CreateImageViews();

	if (!CreateRenderPass()) return false;

	if (!CreateDescriptorSetLayout()) return false;

	if (!CreateGraphicsPipeline()) return false;

	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// VULKAN CREATE INSTANCE
#pragma region VkInstance


static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData)
{
	if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
	{
		std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
	}

	return VK_FALSE;
}

bool
Renderer::CheckValidationSupport()
{
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	std::vector<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	for (const char* layerName : m_pSettings->validationLayers) 
	{
		bool layerFound = false;

		for (const auto& layerProperties : availableLayers) {
			if (strcmp(layerName, layerProperties.layerName) == 0) {
				layerFound = true;
				break;
			}
		}

		if (!layerFound) {
			return false;
		}
	}

	return true;
}

std::vector<const char*>	
Renderer::GetRequiredExtensions()
{
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

	#ifdef _DEBUG
	extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	#endif

	return extensions;
}

void 
Renderer::PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo)
{
	createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	createInfo.pfnUserCallback = debugCallback;
}

VkResult 
Renderer::CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger)
{
	auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
	if (func != nullptr) {
		return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
	}
	else {
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}
}

void 
Renderer::DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator)
{
	auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
	if (func != nullptr) {
		func(instance, debugMessenger, pAllocator);
	}
}

bool
Renderer::CreateVkInstance(VkInstance* result)
{
	VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = {};
	
	#ifdef _DEBUG
	if(!CheckValidationSupport())
	{
		Debug::LogError("validation layers requested, but not available!");
		return false;
	}
	#endif // _DEBUG

	auto extensions = GetRequiredExtensions();

	VkApplicationInfo appInfo = {};
	appInfo.sType				= VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName	= m_pSettings->applicationName;
	appInfo.applicationVersion	= m_pSettings->applicationVersion;
	appInfo.pEngineName			= "Trigon";
	appInfo.engineVersion		= VK_MAKE_API_VERSION(1, 1, 0, 0);
	appInfo.apiVersion			= VK_API_VERSION_1_2;
	appInfo.pNext				= nullptr;

	VkInstanceCreateInfo createInfo = {};
	createInfo.sType					= VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo			= &appInfo;
	createInfo.enabledExtensionCount	= static_cast<uint32_t>(extensions.size());
	createInfo.ppEnabledExtensionNames	= extensions.data();

	#ifdef _DEBUG
	createInfo.enabledLayerCount		= static_cast<uint32_t>(m_pSettings->validationLayers.size());
	createInfo.ppEnabledLayerNames		= m_pSettings->validationLayers.data();

	PopulateDebugMessengerCreateInfo(debugCreateInfo);
	createInfo.pNext					= (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
	#else	
	createInfo.enabledLayerCount		= 0;
	createInfo.ppEnabledLayerNames		= nullptr;
	createInfo.pNext					= nullptr;
	#endif
	createInfo.flags = 0;

	if (vkCreateInstance(&createInfo, nullptr, result) != VK_SUCCESS)
	{
		Debug::LogError("Failed to create vkInstance");
		return false;
	}

	return true;

}

#pragma endregion

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// VULKAN SetupDebugMessenger and SURFACE
#pragma region
void
Renderer::SetupDebugMessenger()
{
#ifdef _DEBUG
	VkDebugUtilsMessengerCreateInfoEXT createInfo;
	PopulateDebugMessengerCreateInfo(createInfo);

	if (CreateDebugUtilsMessengerEXT(m_pContext->instance, &createInfo, nullptr, &m_pContext->debugMessenger) != VK_SUCCESS)
	{
		Debug::LogStatus(DebugType::Create, DebugResult::Failed, DebugColor::Red, "DebugMessenger");
		return;
	}
	Debug::LogStatus(DebugType::Create, DebugResult::Success, DebugColor::Green, "DebugMessenger");
#endif
}

bool 
Renderer::CreateSurface()
{
	if (glfwCreateWindowSurface(m_pContext->instance, m_pWindow->m_pWindow, nullptr, &m_pContext->surface) != VK_SUCCESS)
	{
		Debug::LogStatus(DebugType::Bind, DebugResult::Failed, DebugColor::Red, "Surface");
		return false;
	}
	Debug::LogStatus(DebugType::Bind, DebugResult::Success, DebugColor::Green, "Surface");
	return true;
}

#pragma endregion;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Pick Physical Device
#pragma region PhysicalDevice
SwapChainSupportDetails 
Renderer::QuerySwapChainSupport(VkPhysicalDevice device)
{
	SwapChainSupportDetails details;

	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, m_pContext->surface, &details.capabilities);

	uint32_t formatCount;
	vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_pContext->surface, &formatCount, nullptr);

	if (formatCount != 0) {
		details.formats.resize(formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_pContext->surface, &formatCount, details.formats.data());
	}

	uint32_t presentModeCount;
	vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_pContext->surface, &presentModeCount, nullptr);

	if (presentModeCount != 0) {
		details.presentModes.resize(presentModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_pContext->surface, &presentModeCount, details.presentModes.data());
	}

	return details;
}

bool 
Renderer::CheckDeviceExtensionSupport(VkPhysicalDevice device)
{
	uint32_t extensionCount;
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

	std::vector<VkExtensionProperties> availableExtensions(extensionCount);
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

	std::set<std::string> requiredExtensions(m_pSettings->deviceExtensions.begin(), m_pSettings->deviceExtensions.end());

	for (const auto& extension : availableExtensions) {
		requiredExtensions.erase(extension.extensionName);
	}

	return requiredExtensions.empty();
}

QueueFamilyIndices 
Renderer::FindQueueFamilies(VkPhysicalDevice device)
{
	QueueFamilyIndices indices;

	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

	int i = 0;
	for (const auto& queueFamily : queueFamilies) {
		if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			indices.graphicsFamily = i;
		}

		VkBool32 presentSupport = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(device, i, m_pContext->surface, &presentSupport);

		if (presentSupport)
		{
			indices.presentFamily = i;
		}

		if (indices.isComplete()) {
			break;
		}

		i++;
	}

	return indices;
}

bool 
Renderer::IsDeviceSuitable(VkPhysicalDevice device) 
{
	QueueFamilyIndices indices = FindQueueFamilies(device);

	bool extensionsSupported = CheckDeviceExtensionSupport(device);

	bool swapChainAdequate = false;
	if (extensionsSupported) {
		SwapChainSupportDetails swapChainSupport = QuerySwapChainSupport(device);
		swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
	}

	VkPhysicalDeviceFeatures supportedFeatures;
	vkGetPhysicalDeviceFeatures(device, &supportedFeatures);

	return indices.isComplete() && extensionsSupported && swapChainAdequate && supportedFeatures.samplerAnisotropy;
}

VkSampleCountFlagBits
Renderer::GetMaxUsableSampleCount()
{
	VkPhysicalDeviceProperties physicalDeviceProperties;
	vkGetPhysicalDeviceProperties(m_pContext->physicalDevice, &physicalDeviceProperties);

	VkSampleCountFlags counts = physicalDeviceProperties.limits.framebufferColorSampleCounts & physicalDeviceProperties.limits.framebufferDepthSampleCounts;
	if (counts & VK_SAMPLE_COUNT_64_BIT) { return VK_SAMPLE_COUNT_64_BIT; }
	if (counts & VK_SAMPLE_COUNT_32_BIT) { return VK_SAMPLE_COUNT_32_BIT; }
	if (counts & VK_SAMPLE_COUNT_16_BIT) { return VK_SAMPLE_COUNT_16_BIT; }
	if (counts & VK_SAMPLE_COUNT_8_BIT)  { return VK_SAMPLE_COUNT_8_BIT; }
	if (counts & VK_SAMPLE_COUNT_4_BIT)  { return VK_SAMPLE_COUNT_4_BIT; }
	if (counts & VK_SAMPLE_COUNT_2_BIT)  { return VK_SAMPLE_COUNT_2_BIT; }

	return VK_SAMPLE_COUNT_1_BIT;
}

bool
Renderer::PickPhysicalDevice()
{
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(m_pContext->instance, &deviceCount, nullptr);

	if (deviceCount == 0) 
	{
		Debug::LogStatus(DebugType::Pick, DebugResult::Failed, DebugColor::Red, "Physical Device");
		return false;
	}

	m_pContext->availableDevices = std::vector<VkPhysicalDevice>(deviceCount);

	vkEnumeratePhysicalDevices(m_pContext->instance, &deviceCount, m_pContext->availableDevices.data());

	for (const auto& device : m_pContext->availableDevices)
	{
		if (IsDeviceSuitable(device)) 
		{
			m_pContext->physicalDevice = device;
			m_pContext->msaaSamples = GetMaxUsableSampleCount();
			break;
		}
	}

	if (m_pContext->physicalDevice == VK_NULL_HANDLE)
	{
		Debug::LogStatus(DebugType::Pick, DebugResult::Failed, DebugColor::Red, "Physical Device");
		return false;
	}
	else
	{
		vkGetPhysicalDeviceFeatures(m_pContext->physicalDevice, &m_pContext->deviceFeatures);
		vkGetPhysicalDeviceProperties(m_pContext->physicalDevice, &m_pContext->devicePropterties);
		Debug::LogStatus(DebugType::Pick, DebugResult::Success, DebugColor::Green, "Physical Device");
		Debug::Log("SELECTED: %s", m_pContext->devicePropterties.deviceName);
		return true;
	}
}
#pragma endregion

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Create logical device
#pragma region LogicalDevice
bool						
Renderer::CreateLogicalDevice() 
{
	QueueFamilyIndices indices = FindQueueFamilies(m_pContext->physicalDevice);

	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
	std::set<uint32_t> uniqueQueueFamilies = { indices.graphicsFamily.value(), indices.presentFamily.value() };

	float queuePriority = 1.0f;
	for (uint32_t queueFamily : uniqueQueueFamilies) {
		VkDeviceQueueCreateInfo queueCreateInfo{};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = queueFamily;
		queueCreateInfo.queueCount = 1;
		queueCreateInfo.pQueuePriorities = &queuePriority;
		queueCreateInfos.push_back(queueCreateInfo);
	}

	VkPhysicalDeviceFeatures deviceFeatures{};
	deviceFeatures.samplerAnisotropy = VK_TRUE;

	VkDeviceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

	createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
	createInfo.pQueueCreateInfos = queueCreateInfos.data();

	createInfo.pEnabledFeatures = &deviceFeatures;

	createInfo.enabledExtensionCount = static_cast<uint32_t>(m_pSettings->deviceExtensions.size());
	createInfo.ppEnabledExtensionNames = m_pSettings->deviceExtensions.data();

#ifdef _DEBUG
		createInfo.enabledLayerCount = static_cast<uint32_t>(m_pSettings->validationLayers.size());
		createInfo.ppEnabledLayerNames = m_pSettings->validationLayers.data();
#else
		createInfo.enabledLayerCount = 0;	
#endif

	if (vkCreateDevice(m_pContext->physicalDevice, &createInfo, nullptr, &m_pContext->logicalDevice) != VK_SUCCESS) {
		Debug::LogStatus(DebugType::Create, DebugResult::Failed, DebugColor::Red, "Logical Device");
		return false;
	}

	vkGetDeviceQueue(m_pContext->logicalDevice, indices.graphicsFamily.value(), 0, &m_pContext->graphicsQueue);
	vkGetDeviceQueue(m_pContext->logicalDevice, indices.presentFamily.value(), 0,  &m_pContext->presentQueue);

	Debug::LogStatus(DebugType::Create, DebugResult::Success, DebugColor::Green, "Logical Device");
	return true;
}
#pragma endregion

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Create SwapChain

VkSurfaceFormatKHR 
Renderer::ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
{
	for (const auto& availableFormat : availableFormats) {
		if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
			return availableFormat;
		}
	}

	return availableFormats[0];
}

VkPresentModeKHR 
Renderer::ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
{
	for (const auto& availablePresentMode : availablePresentModes) {
		if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
			return availablePresentMode;
		}
	}

	return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D 
Renderer::ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities)
{
	if (capabilities.currentExtent.width != UINT32_MAX) {
		return capabilities.currentExtent;
	}
	else {
		int width, height;
		glfwGetFramebufferSize(m_pWindow->m_pWindow, &width, &height);

		VkExtent2D actualExtent = {
			static_cast<uint32_t>(width),
			static_cast<uint32_t>(height)
		};

		actualExtent.width	= std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
		actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

		return actualExtent;
	}
}

bool						
Renderer::CreateSwapChain()
{
	SwapChainSupportDetails swapChainSupport = QuerySwapChainSupport(m_pContext->physicalDevice);

	VkSurfaceFormatKHR surfaceFormat	= ChooseSwapSurfaceFormat(swapChainSupport.formats);
	VkPresentModeKHR presentMode		= ChooseSwapPresentMode(swapChainSupport.presentModes);
	VkExtent2D extent					= ChooseSwapExtent(swapChainSupport.capabilities);

	uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
	if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
		imageCount = swapChainSupport.capabilities.maxImageCount;
	}

	VkSwapchainCreateInfoKHR createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	createInfo.surface = m_pContext->surface;

	createInfo.minImageCount = imageCount;
	createInfo.imageFormat = surfaceFormat.format;
	createInfo.imageColorSpace = surfaceFormat.colorSpace;
	createInfo.imageExtent = extent;
	createInfo.imageArrayLayers = 1;
	createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

	QueueFamilyIndices indices = FindQueueFamilies(m_pContext->physicalDevice);
	uint32_t queueFamilyIndices[] = { indices.graphicsFamily.value(), indices.presentFamily.value() };

	if (indices.graphicsFamily != indices.presentFamily) {
		createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		createInfo.queueFamilyIndexCount = 2;
		createInfo.pQueueFamilyIndices = queueFamilyIndices;
	}
	else {
		createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	}

	createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
	createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	createInfo.presentMode = presentMode;
	createInfo.clipped = VK_TRUE;

	if (vkCreateSwapchainKHR(m_pContext->logicalDevice, &createInfo, nullptr, &m_pContext->swapChain) != VK_SUCCESS)
	{
		Debug::LogStatus(DebugType::Create, DebugResult::Failed, DebugColor::Red, "SwapChain");
		return false;
	}

	vkGetSwapchainImagesKHR(m_pContext->logicalDevice, m_pContext->swapChain, &imageCount, nullptr);
	m_pContext->swapChainImages.resize(imageCount);
	vkGetSwapchainImagesKHR(m_pContext->logicalDevice, m_pContext->swapChain, &imageCount, m_pContext->swapChainImages.data());

	m_pContext->swapChainImageFormat = surfaceFormat.format;
	m_pContext->swapChainExtent = extent;
	Debug::LogStatus(DebugType::Create, DebugResult::Success, DebugColor::Green, "SwapChain");
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Create Image Views

VkImageView 
Renderer::CreateImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels)
{
	VkImageViewCreateInfo viewInfo{};
	viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	viewInfo.image = image;
	viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
	viewInfo.format = format;
	viewInfo.subresourceRange.aspectMask = aspectFlags;
	viewInfo.subresourceRange.baseMipLevel = 0;
	viewInfo.subresourceRange.levelCount = mipLevels;
	viewInfo.subresourceRange.baseArrayLayer = 0;
	viewInfo.subresourceRange.layerCount = 1;

	VkImageView imageView;
	if (vkCreateImageView(m_pContext->logicalDevice, &viewInfo, nullptr, &imageView) != VK_SUCCESS)
	{
		Debug::LogStatus(DebugType::Create, DebugResult::Failed, DebugColor::Red, "ImageView");
	}
	Debug::LogStatus(DebugType::Create, DebugResult::Success, DebugColor::Green, "ImageView");
	return imageView;
}

void 
Renderer::CreateImageViews()
{
	m_pContext->swapChainImageViews.resize(m_pContext->swapChainImages.size());

	for (uint32_t i = 0; i < m_pContext->swapChainImages.size(); i++) {
		m_pContext->swapChainImageViews[i] = CreateImageView(m_pContext->swapChainImages[i], m_pContext->swapChainImageFormat, VK_IMAGE_ASPECT_COLOR_BIT, 1);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Create RenderPass

VkFormat 
Renderer::FindSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features)
{
	for (VkFormat format : candidates) {
		VkFormatProperties props;
		vkGetPhysicalDeviceFormatProperties(m_pContext->physicalDevice, format, &props);

		if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features) {
			return format;
		}
		else if (tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features) {
			return format;
		}
	}

	throw std::runtime_error("failed to find supported format!");
}

VkFormat 
Renderer::FindDepthFormat()
{
	return FindSupportedFormat(
		{ VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT },
		VK_IMAGE_TILING_OPTIMAL,
		VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT
	);
}

bool
Renderer::CreateRenderPass()
{
	VkAttachmentDescription colorAttachment{};
	colorAttachment.format = m_pContext->swapChainImageFormat;
	colorAttachment.samples = m_pContext->msaaSamples;
	colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	colorAttachment.finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	VkAttachmentDescription depthAttachment{};
	depthAttachment.format = FindDepthFormat();
	depthAttachment.samples = m_pContext->msaaSamples;
	depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	depthAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

	VkAttachmentDescription colorAttachmentResolve{};
	colorAttachmentResolve.format = m_pContext->swapChainImageFormat;
	colorAttachmentResolve.samples = VK_SAMPLE_COUNT_1_BIT;
	colorAttachmentResolve.loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	colorAttachmentResolve.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	colorAttachmentResolve.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	colorAttachmentResolve.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	colorAttachmentResolve.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	colorAttachmentResolve.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

	VkAttachmentReference colorAttachmentRef{};
	colorAttachmentRef.attachment = 0;
	colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	VkAttachmentReference depthAttachmentRef{};
	depthAttachmentRef.attachment = 1;
	depthAttachmentRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

	VkAttachmentReference colorAttachmentResolveRef{};
	colorAttachmentResolveRef.attachment = 2;
	colorAttachmentResolveRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	VkSubpassDescription subpass{};
	subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	subpass.colorAttachmentCount = 1;
	subpass.pColorAttachments = &colorAttachmentRef;
	subpass.pDepthStencilAttachment = &depthAttachmentRef;
	subpass.pResolveAttachments = &colorAttachmentResolveRef;

	VkSubpassDependency dependency{};
	dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
	dependency.dstSubpass = 0;
	dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
	dependency.srcAccessMask = 0;
	dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
	dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

	std::array<VkAttachmentDescription, 3> attachments = { colorAttachment, depthAttachment, colorAttachmentResolve };
	VkRenderPassCreateInfo renderPassInfo{};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	renderPassInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
	renderPassInfo.pAttachments = attachments.data();
	renderPassInfo.subpassCount = 1;
	renderPassInfo.pSubpasses = &subpass;
	renderPassInfo.dependencyCount = 1;
	renderPassInfo.pDependencies = &dependency;

	if (vkCreateRenderPass(m_pContext->logicalDevice, &renderPassInfo, nullptr, &m_pContext->renderPass) != VK_SUCCESS)
	{
		Debug::LogStatus(DebugType::Create, DebugResult::Failed, DebugColor::Red, "RenderPass");
		return false;
	}
	Debug::LogStatus(DebugType::Create, DebugResult::Success, DebugColor::Green, "RenderPass");
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Create DescriptorSetLayout

bool
Renderer::CreateDescriptorSetLayout()
{
	VkDescriptorSetLayoutBinding uboLayoutBinding{};
	uboLayoutBinding.binding = 0;
	uboLayoutBinding.descriptorCount = 1;
	uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	uboLayoutBinding.pImmutableSamplers = nullptr;
	uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

	VkDescriptorSetLayoutBinding samplerLayoutBinding{};
	samplerLayoutBinding.binding = 1;
	samplerLayoutBinding.descriptorCount = 1;
	samplerLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	samplerLayoutBinding.pImmutableSamplers = nullptr;
	samplerLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;

	std::array<VkDescriptorSetLayoutBinding, 2> bindings = { uboLayoutBinding, samplerLayoutBinding };
	VkDescriptorSetLayoutCreateInfo layoutInfo{};
	layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	layoutInfo.bindingCount = static_cast<uint32_t>(bindings.size());
	layoutInfo.pBindings = bindings.data();

	if (vkCreateDescriptorSetLayout(m_pContext->logicalDevice, &layoutInfo, nullptr, &m_pContext->descriptorSetLayout) != VK_SUCCESS) {
		Debug::LogStatus(DebugType::Create, DebugResult::Failed, DebugColor::Red, "Descriptor");
		return false;
	}
	Debug::LogStatus(DebugType::Create, DebugResult::Success, DebugColor::Green, "Descriptor");
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Create Graphics Pipeline

std::array<VkVertexInputAttributeDescription, 3>
Vertex::GetAttributeDescriptions() 
{
	
	std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions{};

	attributeDescriptions[0].binding = 0;
	attributeDescriptions[0].location = 0;
	attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
	attributeDescriptions[0].offset = offsetof(Vertex, pos);

	attributeDescriptions[1].binding = 0;
	attributeDescriptions[1].location = 1;
	attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
	attributeDescriptions[1].offset = offsetof(Vertex, color);

	attributeDescriptions[2].binding = 0;
	attributeDescriptions[2].location = 2;
	attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
	attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

	return attributeDescriptions;
	

}

VkVertexInputBindingDescription 
Vertex::GetBindingDescription()
{
	VkVertexInputBindingDescription bindingDescription{};
	bindingDescription.binding = 0;
	bindingDescription.stride = sizeof(Vertex);
	bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

	return bindingDescription;
}


std::vector<char> 
Renderer::ReadFile(const std::string& filename)
{
	std::ifstream file(filename, std::ios::ate | std::ios::binary);

	if (!file.is_open()) 
	{
		Debug::LogError("Could not open file: %s", filename);
		return std::vector<char>();
	}

	size_t fileSize = (size_t)file.tellg();
	std::vector<char> buffer(fileSize);

	file.seekg(0);
	file.read(buffer.data(), fileSize);

	file.close();

	return buffer;
}

VkShaderModule 
Renderer::CreateShaderModule(const std::vector<char>& code)
{
	VkShaderModuleCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = code.size();
	createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

	VkShaderModule shaderModule;
	if (vkCreateShaderModule(m_pContext->logicalDevice, &createInfo, nullptr, &shaderModule) != VK_SUCCESS)
	{
		Debug::LogError("Shader is not valid!");
		return shaderModule;
	}

	return shaderModule;
}

bool 
Renderer::CreateGraphicsPipeline()
{
	auto vertShaderCode = ReadFile("assets/shaders/vert.spv");
	auto fragShaderCode = ReadFile("assets/shaders/frag.spv");

	VkShaderModule vertShaderModule = CreateShaderModule(vertShaderCode);
	VkShaderModule fragShaderModule = CreateShaderModule(fragShaderCode);
	if (!vertShaderModule || !fragShaderModule) return false;

	VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
	vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
	vertShaderStageInfo.module = vertShaderModule;
	vertShaderStageInfo.pName = "main";

	VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
	fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	fragShaderStageInfo.module = fragShaderModule;
	fragShaderStageInfo.pName = "main";

	VkPipelineShaderStageCreateInfo shaderStages[] = { vertShaderStageInfo, fragShaderStageInfo };

	VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
	vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

	auto bindingDescription		=	Vertex::GetBindingDescription();
	auto attributeDescriptions	=	Vertex::GetAttributeDescriptions();

	vertexInputInfo.vertexBindingDescriptionCount	= 1;
	vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
	vertexInputInfo.pVertexBindingDescriptions		= &bindingDescription;
	vertexInputInfo.pVertexAttributeDescriptions	= attributeDescriptions.data();

	VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
	inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	inputAssembly.primitiveRestartEnable = VK_FALSE;

	VkViewport viewport{};
	viewport.x			= 0.0f;
	viewport.y			= 0.0f;
	viewport.width		= (float)m_pContext->swapChainExtent.width;
	viewport.height		= (float)m_pContext->swapChainExtent.height;
	viewport.minDepth	= 0.0f;
	viewport.maxDepth	= 1.0f;

	VkRect2D scissor{};
	scissor.offset = { 0, 0 };
	scissor.extent = m_pContext->swapChainExtent;

	VkPipelineViewportStateCreateInfo viewportState{};
	viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	viewportState.viewportCount = 1;
	viewportState.pViewports = &viewport;
	viewportState.scissorCount = 1;
	viewportState.pScissors = &scissor;

	VkPipelineRasterizationStateCreateInfo rasterizer{};
	rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	rasterizer.depthClampEnable = VK_FALSE;
	rasterizer.rasterizerDiscardEnable = VK_FALSE;
	rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
	rasterizer.lineWidth = 1.0f;
	rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
	rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
	rasterizer.depthBiasEnable = VK_FALSE;

	VkPipelineMultisampleStateCreateInfo multisampling{};
	multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	multisampling.sampleShadingEnable = VK_FALSE;
	multisampling.rasterizationSamples = m_pContext->msaaSamples;

	VkPipelineDepthStencilStateCreateInfo depthStencil{};
	depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
	depthStencil.depthTestEnable = VK_TRUE;
	depthStencil.depthWriteEnable = VK_TRUE;
	depthStencil.depthCompareOp = VK_COMPARE_OP_LESS;
	depthStencil.depthBoundsTestEnable = VK_FALSE;
	depthStencil.stencilTestEnable = VK_FALSE;

	VkPipelineColorBlendAttachmentState colorBlendAttachment{};
	colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	colorBlendAttachment.blendEnable = VK_FALSE;

	VkPipelineColorBlendStateCreateInfo colorBlending{};
	colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	colorBlending.logicOpEnable = VK_FALSE;
	colorBlending.logicOp = VK_LOGIC_OP_COPY;
	colorBlending.attachmentCount = 1;
	colorBlending.pAttachments = &colorBlendAttachment;
	colorBlending.blendConstants[0] = 0.0f;
	colorBlending.blendConstants[1] = 0.0f;
	colorBlending.blendConstants[2] = 0.0f;
	colorBlending.blendConstants[3] = 0.0f;

	VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutInfo.setLayoutCount = 1;
	pipelineLayoutInfo.pSetLayouts = &m_pContext->descriptorSetLayout;

	if (vkCreatePipelineLayout(m_pContext->logicalDevice, &pipelineLayoutInfo, nullptr, &m_pContext->pipelineLayout) != VK_SUCCESS) 
	{
		Debug::LogStatus(DebugType::Create, DebugResult::Failed, DebugColor::Red, "PipelineLayout");
		return false;
	}
	Debug::LogStatus(DebugType::Create, DebugResult::Success, DebugColor::Green, "PipelineLayout");

	VkGraphicsPipelineCreateInfo pipelineInfo{};
	pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pipelineInfo.stageCount = 2;
	pipelineInfo.pStages = shaderStages;
	pipelineInfo.pVertexInputState = &vertexInputInfo;
	pipelineInfo.pInputAssemblyState = &inputAssembly;
	pipelineInfo.pViewportState = &viewportState;
	pipelineInfo.pRasterizationState = &rasterizer;
	pipelineInfo.pMultisampleState = &multisampling;
	pipelineInfo.pDepthStencilState = &depthStencil;
	pipelineInfo.pColorBlendState = &colorBlending;
	pipelineInfo.layout			 = m_pContext->pipelineLayout;
	pipelineInfo.renderPass = m_pContext->renderPass;
	pipelineInfo.subpass = 0;
	pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

	if (vkCreateGraphicsPipelines(m_pContext->logicalDevice, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &m_pContext->graphicsPipeline) != VK_SUCCESS)
	{
		Debug::LogStatus(DebugType::Create, DebugResult::Failed, DebugColor::Red, "Pipeline");
		return false;
	}
	Debug::LogStatus(DebugType::Create, DebugResult::Success, DebugColor::Green, "Pipeline");

	vkDestroyShaderModule(m_pContext->logicalDevice, fragShaderModule, nullptr);
	vkDestroyShaderModule(m_pContext->logicalDevice, vertShaderModule, nullptr);
	return true;
}