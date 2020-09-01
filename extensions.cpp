#pragma once

#include <vulkan/vulkan.h>
#include <cstdlib>
#include <vector>
#include <set>
#include <string>

typedef const std::vector<const char*> extNames;

bool extensionsSupported(VkPhysicalDevice *pDev, extNames *extensions) {
	uint32_t extensionCount;
	vkEnumerateDeviceExtensionProperties(*pDev, nullptr, &extensionCount, nullptr);

	std::vector<VkExtensionProperties> availableExtensions(extensionCount);
	vkEnumerateDeviceExtensionProperties(*pDev, nullptr, &extensionCount, availableExtensions.data());

	std::set<std::string> requiredExtensions(extensions->begin(), extensions->end());

	for (const auto& extension : availableExtensions)
		requiredExtensions.erase(extension.extensionName);

	return requiredExtensions.empty();
}
