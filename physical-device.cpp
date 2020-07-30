#include <vulkan/vulkan.h>
#include <iostream>
#include "queue.cpp"

bool isDeviceSuitable(PhysicalDeviceQueueFamilyIndices device);

PhysicalDeviceQueueFamilyIndices createPhysDev(VkInstance instance, VkSurfaceKHR surface) {
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());
	PhysicalDeviceQueueFamilyIndices devInds;

	for (const auto& device : devices) {
		devInds.dev = device;
		devInds.inds = findQueueFamilies(device, surface);
		if (isDeviceSuitable(devInds)) {
			break;
		}
	}	

	if (!deviceCount || !isDeviceSuitable(devInds)) {
		throw std::runtime_error("failed to find GPU to satisfy requiremnts");
	}

	return devInds;
}

//TODO this function seems like may need to be contantly expanded based on the specifics of the program. Ideally there would be only one such function and it would be referenced directly by main
bool isDeviceSuitable(PhysicalDeviceQueueFamilyIndices devInds) {
	/*
	VkPhysicalDeviceProperties deviceProperties;
	vkGetPhysicalDeviceProperties(device, &deviceProperties);

	VkPhysicalDeviceFeatures deviceFeatures;
	vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
	*/
	return devInds.inds.isComplete();
}

