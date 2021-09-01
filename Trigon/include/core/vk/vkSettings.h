#ifndef VKSETTINGS_H
#define VKSETTINGS_H
#include "Backend.h"
#include <vector>
// TODO:
// Serialize to file

class vkSettings
{
public:
	const char* applicationName			= "New Project";
	int			applicationVersion		= VK_MAKE_API_VERSION(1,1, 0, 0);




	const std::vector<const char*> validationLayers =
	{
		"VK_LAYER_KHRONOS_validation"
	};

	const std::vector<const char*> deviceExtensions = 
	{
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};
};


#endif // !VKSETTINGS_H