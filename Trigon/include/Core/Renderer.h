#ifndef RENDERER_H
#define RENDERER_H
#include "vk/Backend.h"
#include "vk/vkSettings.h"
#include <optional>
#include "math\Vector3.h"
#include "math\Matrix4.h"
#include "math\Vector2.h"

class WindowPtr;

struct SwapChainSupportDetails
{
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

struct QueueFamilyIndices
{
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	bool isComplete() {
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};

struct vkContext
{
	VkInstance									instance;
	VkDebugUtilsMessengerEXT					debugMessenger;
	VkDevice									logicalDevice;
	VkQueue										presentQueue;
	VkQueue										graphicsQueue;
	VkPhysicalDevice							physicalDevice;
	VkPhysicalDeviceFeatures					deviceFeatures;
	VkPhysicalDeviceProperties					devicePropterties;
	VkSurfaceKHR								surface;
	VkSwapchainKHR								swapChain;
	VkFormat									swapChainImageFormat;
	VkExtent2D									swapChainExtent;
	VkRenderPass								renderPass;
	VkDescriptorSetLayout						descriptorSetLayout;
	VkPipelineLayout							pipelineLayout;
	VkPipeline									graphicsPipeline;

	std::vector<VkImage>						swapChainImages;
	std::vector<VkImageView>					swapChainImageViews;
	std::vector<VkFramebuffer>					swapChainFramebuffers;
	std::vector<VkPhysicalDevice>				availableDevices;


	VkSampleCountFlagBits						msaaSamples = VK_SAMPLE_COUNT_1_BIT;

};

struct Vertex {
	Vector3 pos;
	Vector3 color;
	Vector2 texCoord;

	static VkVertexInputBindingDescription GetBindingDescription();

	static std::array<VkVertexInputAttributeDescription, 3> GetAttributeDescriptions();

	bool operator==(const Vertex& other) const 
	{
		return pos == const_cast<Vector3&>(other.pos) && color == const_cast<Vector3&>(other.color) && texCoord == const_cast<Vector2&>(other.texCoord);
	}
};

class Renderer
{
private:
	WindowPtr*				m_pWindow;
	vkContext*				m_pContext;
	vkSettings*				m_pSettings;
	static Renderer*		m_pRenderer;

///////////////////////////////////////////////////////////

public:

	// Renderer Logic

	static Renderer*			CreateInstance();
	static Renderer*			GetInstance();
	static void					DestroyInstance();
	void						CleanupSwapChain();

///////////////////////////////////////////////////////////
	
protected:

	//Vulkan Create Instance
	
	bool						Init();
	bool						CreateVkInstance(VkInstance* result);
	std::vector<const char*>	GetRequiredExtensions();
	void						DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
	VkResult					CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
	void						PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
	bool						CheckValidationSupport();

///////////////////////////////////////////////////////////

	//Vulkan Debug and Surface
	void						SetupDebugMessenger();

	bool						CreateSurface();

///////////////////////////////////////////////////////////

	// Vulkan Pick Physical Device

	bool						CheckDeviceExtensionSupport(VkPhysicalDevice device);
	SwapChainSupportDetails		QuerySwapChainSupport(VkPhysicalDevice device);
	bool						IsDeviceSuitable(VkPhysicalDevice device);VkSampleCountFlagBits		GetMaxUsableSampleCount();
	QueueFamilyIndices			FindQueueFamilies(VkPhysicalDevice device);
	bool						PickPhysicalDevice();

///////////////////////////////////////////////////////////

	// Vulkan Create Logical Device

	bool						CreateLogicalDevice();

///////////////////////////////////////////////////////////

	// Vulkan Create SwapChain
	VkSurfaceFormatKHR			ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR			ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D					ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
	bool						CreateSwapChain();
///////////////////////////////////////////////////////////

	// Vulkan Create Image Views

	VkImageView CreateImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels);

	void		CreateImageViews();


///////////////////////////////////////////////////////////

	// Vulkan Create RenderPass
	VkFormat	FindSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
	VkFormat	FindDepthFormat();
	bool		CreateRenderPass();

///////////////////////////////////////////////////////////

	// Vulkan DescriptorSetLayout

	bool		CreateDescriptorSetLayout();

	///////////////////////////////////////////////////////////

	// Vulkan GraphicsPipeline

	std::vector<char> ReadFile(const std::string& filename);

	VkShaderModule	CreateShaderModule(const std::vector<char>& code);

	bool			CreateGraphicsPipeline();

};


#endif // !RENDERER_H