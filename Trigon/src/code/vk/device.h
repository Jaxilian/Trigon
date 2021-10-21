#ifndef DEVICE_H
#define DEVICE_H
#include "win/win.h"
#include <vector>


struct SwapChainSupportDetails 
{
  VkSurfaceCapabilitiesKHR capabilities;
  std::vector<VkSurfaceFormatKHR> formats;
  std::vector<VkPresentModeKHR> presentModes;
};

struct QueueFamilyIndices 
{
  uint32_t graphicsFamily;
  uint32_t presentFamily;
  bool graphicsFamilyHasValue = false;
  bool presentFamilyHasValue = false;
  bool isComplete() { return graphicsFamilyHasValue && presentFamilyHasValue; }
};

namespace device
{
    VkCommandPool   getCommandPool();
    VkDevice        get();
    VkSurfaceKHR    getSurface();
    VkQueue         getGraphicsQueue();
    VkQueue         getPresentQueue();

    SwapChainSupportDetails getSwapChainSupport();
    uint32_t                findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
    QueueFamilyIndices      findPhysicalQueueFamilies();
    VkFormat                findSupportedFormat(const std::vector<VkFormat> &candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

    void create();
    void release();
}

#endif