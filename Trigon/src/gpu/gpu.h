#ifndef GPU_H
#define GPU_H
#include "../libref.h"

struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

struct QueueFamilyIndices {
	uint32_t graphicsFamily;
	uint32_t presentFamily;
	bool graphicsFamilyHasValue = false;
	bool presentFamilyHasValue = false;
	bool isComplete() { return graphicsFamilyHasValue && presentFamilyHasValue; }
};

struct ShaderPipeline 
{
	VkPipeline pipeline;
	VkShaderModule vertShader;
	VkShaderModule fragShader;
};

struct PipelineConfiguration 
{
	std::vector<VkVertexInputBindingDescription>	bindingDescriptions{};
	std::vector<VkVertexInputAttributeDescription>	attributeDescriptions{};
	VkPipelineViewportStateCreateInfo				viewportInfo;
	VkPipelineInputAssemblyStateCreateInfo			inputAssemblyInfo;
	VkPipelineRasterizationStateCreateInfo			rasterizationInfo;
	VkPipelineMultisampleStateCreateInfo			multisampleInfo;
	VkPipelineColorBlendAttachmentState				colorBlendAttachment;
	VkPipelineColorBlendStateCreateInfo				colorBlendInfo;
	VkPipelineDepthStencilStateCreateInfo			depthStencilInfo;
	std::vector<VkDynamicState>						dynamicStateEnables;
	VkPipelineDynamicStateCreateInfo				dynamicStateInfo;
	VkPipelineLayout								pipelineLayout = nullptr;
	VkRenderPass									renderPass = nullptr;
	uint32_t										subpass = 0;
};

namespace vk_instance 
{
	void create();
	VkInstance& get();
	void destroy();	
}

namespace vk_surface 
{
	void create(GLFWwindow* window);
	VkSurfaceKHR& get();
	void destroy();
}

namespace vk_physical_device 
{
	void				create();
	VkPhysicalDevice&	get();
	QueueFamilyIndices	find_queue_families();
	const std::vector<const char*>& extensions();
	SwapChainSupportDetails get_swapchain_support();
	VkFormat find_supported_formats(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
	void				destroy();
}

namespace vk_logical_device 
{
	void create();
	VkDevice& get();
	VkQueue& graphics_queue();
	VkQueue& present_queue();
	void create_image_with_info(const VkImageCreateInfo& imageInfo,VkMemoryPropertyFlags properties,VkImage& image,VkDeviceMemory& imageMemory);
	void destroy();
}

namespace vk_pipeline 
{
	uint32_t create(const char* path, const char* shaderName, PipelineConfiguration& config);
	const ShaderPipeline* get(uint32_t id);
	void set_pipeline_to_default(PipelineConfiguration& configInfo);
	void bind(VkCommandBuffer commandBuffer, uint32_t shaderPipeline);
	void destroy(uint32_t id);
	void release();
}

namespace vk_swapchain 
{
	void create();
	void destroy();
}

namespace vk_descriptor_pool 
{
	void create(uint32_t maxSets, VkDescriptorPoolCreateFlags poolFlags, const std::vector<VkDescriptorPoolSize>& poolSizes);
	VkDescriptorPool& get();
	void destroy();
}

namespace vk_renderer 
{

}

#endif // !GPU_H
