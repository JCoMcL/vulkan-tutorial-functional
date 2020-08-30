#include <vulkan/vulkan.h>
#include <iostream>
#include <set>
#include "queue.cpp"

bool isDeviceSuitable(PhysicalDeviceQueueFamilyIndices device);
bool extensionsSupported(VkPhysicalDevice pDev, std::vector<const char*> extensions);

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
	const std::vector<const char*> extensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME }; //TODO: clearly this doesn't belong here
	return (
		devInds.inds.isComplete() &&
		extensionsSupported(devInds.dev, extensions)
	);
} 

bool extensionsSupported(VkPhysicalDevice pDev, std::vector<const char*> extensions) {
	uint32_t extensionCount;
	vkEnumerateDeviceExtensionProperties(pDev, nullptr, &extensionCount, nullptr);

	std::vector<VkExtensionProperties> availableExtensions(extensionCount);
	vkEnumerateDeviceExtensionProperties(pDev, nullptr, &extensionCount, availableExtensions.data());

	std::set<std::string> requiredExtensions(extensions.begin(), extensions.end());

	for (const auto& extension : availableExtensions)
		requiredExtensions.erase(extension.extensionName);

	return requiredExtensions.empty();
}
