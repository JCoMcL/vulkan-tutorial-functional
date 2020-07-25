#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <optional>

struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;
	bool isComplete() { return graphicsFamily.has_value(); }
};

//TODO: compile/find a list of queue families
QueueFamilyIndices findQueueFamilies(VkPhysicalDevice dev) {
	QueueFamilyIndices inds;

	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(dev, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(dev, &queueFamilyCount, queueFamilies.data());

	int i = 0;
	for (const auto& queueFamily : queueFamilies) {
		if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			inds.graphicsFamily = i;
		}
		if (inds.isComplete()) { break; }

		i++;
	}

	return inds;
}