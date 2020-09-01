#include <vulkan/vulkan.h>
#include <iostream>
#include <set>
#include "queue.cpp"
#include "extensions.cpp"

bool isDeviceSuitable(PhysicalDeviceQueueFamilyIndices device, extNames *extensions);

PhysicalDeviceQueueFamilyIndices createPhysDev(VkInstance instance, VkSurfaceKHR surface, extNames *extensions) {
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());
	PhysicalDeviceQueueFamilyIndices devInds;

	for (const auto& device : devices) {
		devInds.dev = device;
		devInds.inds = findQueueFamilies(device, surface);
		if (isDeviceSuitable(devInds, extensions)) {
			break;
		}
	}	

	if (!deviceCount || !isDeviceSuitable(devInds, extensions)) {
		throw std::runtime_error("failed to find GPU to satisfy requiremnts");
	}

	return devInds;
}

//TODO this function seems like may need to be contantly expanded based on the specifics of the program. Ideally there would be only one such function and it would be referenced directly by main
bool isDeviceSuitable(PhysicalDeviceQueueFamilyIndices devInds, extNames *extensions) {
	return (
		devInds.inds.isComplete() &&
		extensionsSupported(&devInds.dev, extensions)
	);
} 

