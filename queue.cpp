#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <iostream>
#include <optional>

struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	bool isComplete() { return graphicsFamily.has_value() && presentFamily.has_value(); }
};

struct PhysicalDeviceQueueFamilyIndices {
	VkPhysicalDevice dev;
	QueueFamilyIndices inds;
};

//TODO this function seems like may need to be constantly expanded based on the specifics of the program. Ideally there would be only one such function and it would be referenced directly by main
QueueFamilyIndices findQueueFamilies(VkPhysicalDevice dev, VkSurfaceKHR surface) {
	QueueFamilyIndices indices;

	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(dev, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(dev, &queueFamilyCount, queueFamilies.data());

	int i = 0;
	for (const auto& queueFamily : queueFamilies) {

		//TODO minimise number of queues, prefer queues which satisfy multiple dependencies
		VkBool32 presentSupport = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(dev, i, surface, &presentSupport);
		if ( presentSupport )
			indices.presentFamily = i;

		if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			indices.graphicsFamily = i;

		if (indices.isComplete()) { break; }

		i++;
	}

	if (indices.isComplete())
		return indices;
	else 
		throw std::runtime_error("failed to satisfy queue family requirements");
}
