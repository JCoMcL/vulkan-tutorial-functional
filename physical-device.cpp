#include <vulkan/vulkan.h>
#include <iostream>
#include "queue.cpp"

bool isDeviceSuitable(PhysicalDeviceQueueFamilyIndices device);

PhysicalDeviceQueueFamilyIndices createPhysDev(VkInstance instance) {
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());
	PhysicalDeviceQueueFamilyIndices devInds;

	for (const auto& device : devices) {
		devInds.dev = device;
		devInds.inds = findQueueFamilies(device);
		if (isDeviceSuitable(devInds)) {
			break;
		}
	}	

	if (deviceCount == 0) {
		throw std::runtime_error("failed to find GPUs with Vulkan support!");
	}

	return devInds;
}

bool isDeviceSuitable(PhysicalDeviceQueueFamilyIndices devInds) {
	/*
	VkPhysicalDeviceProperties deviceProperties;
	vkGetPhysicalDeviceProperties(device, &deviceProperties);

	VkPhysicalDeviceFeatures deviceFeatures;
	vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
	*/
	return devInds.inds.isComplete();
}

