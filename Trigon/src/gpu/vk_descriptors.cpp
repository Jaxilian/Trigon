#include "gpu.h"
#include <iostream>
static VkDescriptorPool pool = VK_NULL_HANDLE;


void 
vk_descriptor_pool::create(uint32_t maxSets, VkDescriptorPoolCreateFlags poolFlags, const std::vector<VkDescriptorPoolSize>& poolSizes)
{
	VkDescriptorPoolCreateInfo descriptorPoolInfo{};
	descriptorPoolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	descriptorPoolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
	descriptorPoolInfo.pPoolSizes = poolSizes.data();
	descriptorPoolInfo.maxSets = maxSets;
	descriptorPoolInfo.flags = poolFlags;

	if (vkCreateDescriptorPool(vk_logical_device::get(), &descriptorPoolInfo, nullptr, &pool) !=
		VK_SUCCESS) {
		throw std::runtime_error("failed to create descriptor pool!");
	}
}


VkDescriptorPool& 
vk_descriptor_pool::get() 
{
	return pool;
}


void 
vk_descriptor_pool::destroy() 
{
	vkDestroyDescriptorPool(vk_logical_device::get(), pool, nullptr);
}