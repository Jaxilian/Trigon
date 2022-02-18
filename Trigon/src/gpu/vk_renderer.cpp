#include "gpu.h"
#include <cassert>

uint32_t						currentImageIndex;
bool							isFrameStarted;
std::vector<VkCommandBuffer>	buffers;

VkCommandBuffer begin_frame() 
{
	return VK_NULL_HANDLE;
}

void end_frame() 
{

}

void begin_swapchain_renderpass(VkCommandBuffer buffer) 
{

}

void end_swapchain_renderpass(VkCommandBuffer buffer)
{

}

VkRenderPass get_swapchain_renderpass() 
{
	// return swapcvhain
	return VK_NULL_HANDLE;
}

VkCommandBuffer get_current_command_buffer() 
{
	assert(isFrameStarted && "Can't get command buffer when frame is not started");
	return buffers[currentImageIndex];
}

bool is_frame_in_progress() 
{
	return isFrameStarted;
}