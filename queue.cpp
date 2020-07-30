#pragma once
#include <vulkan/vulkan.h>
#include <vector>
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

//TODO: compile/find a list of queue families
QueueFamilyIndices findQueueFamilies(VkPhysicalDevice dev) {
	PhysicalDeviceQueueFamilyIndices devInds;
	devInds.dev = dev;

	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(dev, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(dev, &queueFamilyCount, queueFamilies.data());

	int i = 0;
	for (const auto& queueFamily : queueFamilies) {
		if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			devInds.inds.graphicsFamily = i;
		}
		if (devInds.inds.isComplete()) { break; }

		i++;
	}

	return devInds.inds;
}
