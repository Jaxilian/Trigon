#ifndef DEVIVE_H
#define DEVICE_H

#include <string>
#include <vector>

#include "vulkan/vulkan.h"

struct SwapChainSupportDetails 
{
  VkSurfaceCapabilitiesKHR          capabilities;
  std::vector<VkSurfaceFormatKHR>   formats;
  std::vector<VkPresentModeKHR>     presentModes;
};

struct QueueFamilyIndices 
{
  uint32_t              graphicsFamily;
  uint32_t              presentFamily;
  bool                  graphicsFamilyHasValue = false;
  bool                  presentFamilyHasValue = false;
  bool isComplete() { return graphicsFamilyHasValue && presentFamilyHasValue; }
};

namespace device
{
    void                        create();
    void                        release();
    VkCommandPool               getCmdPool();
    VkDevice                    get();
    VkSurfaceKHR                getSurface();
    VkQueue                     getGraphicsQueue();
    VkQueue                     getPresentQueue();
    SwapChainSupportDetails     getSwapSupp();
    uint32_t                    findMemType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
    QueueFamilyIndices          findPhyQueueFamilies();
    VkFormat                    findSupportedFormat(const std::vector<VkFormat> &candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

    void            createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags prop, VkBuffer& buf, VkDeviceMemory &bufmem);
    VkCommandBuffer beginSingleTimeCommands();
    void            endSingleTimeCommands(VkCommandBuffer commandBuffer);
    void            copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
    void            copyBufferToImage( VkBuffer buffer, VkImage image, uint32_t width, uint32_t height, uint32_t layerCount);
    void            createImageWithInfo(const VkImageCreateInfo &imageInfo, VkMemoryPropertyFlags properties, VkImage &image, VkDeviceMemory &imageMemory);
    
} // namespace device

#endif

