#include <vulkan/vulkan.h>
#include <iostream>
#include "queue.cpp"

bool isDeviceSuitable(VkPhysicalDevice device);

VkPhysicalDevice getPhysDev(VkInstance instance) {
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());
	VkPhysicalDevice pd;
	for (const auto& device : devices) {
		if (isDeviceSuitable(device)) {
			pd = device;
			break;
		}
	}	

	if (deviceCount == 0) {
		throw std::runtime_error("failed to find GPUs with Vulkan support!");
	}

	return pd;
}

bool isDeviceSuitable(VkPhysicalDevice device) {
	/*
	VkPhysicalDeviceProperties deviceProperties;
	vkGetPhysicalDeviceProperties(device, &deviceProperties);

	VkPhysicalDeviceFeatures deviceFeatures;
	vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
	*/
	QueueFamilyIndices indices = findQueueFamilies(device);

	return indices.isComplete();
}

