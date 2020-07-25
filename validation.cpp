#pragma once
#include <cstring>
#include <vector>
#include <iostream>

#ifndef unint32_t
	#include <vulkan/vulkan.h>
#endif

const std::vector<const char*> validationLayers = {
	"VK_LAYER_KHRONOS_validation"
};

#ifdef NDEBUG
	const bool enableValidationLayers = false;
#else
	const bool enableValidationLayers = true;
#endif

bool checkValidationLayerSupport() {
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	std::vector<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	for (const char* layerName : validationLayers) {
		bool layerFound = false;

		for (const auto& layerProperties : availableLayers) {
			if (strcmp(layerName, layerProperties.layerName) == 0) {
				layerFound = true;
				break;
			}
		}

		if (!layerFound) {
			return false;
		}
	}

	return true;
}

void reportValidationLayerSupport() {
	if (enableValidationLayers && !checkValidationLayerSupport()) {
		throw std::runtime_error("validation layers requested, but not available!");
	}
}

void addEnabledValidationLayers(VkInstanceCreateInfo *createInfo){
	std::cout << "test\n";
	if (enableValidationLayers) {
		createInfo->enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		createInfo->ppEnabledLayerNames = validationLayers.data();
	} else {
		createInfo->enabledLayerCount = 0;
	}
}
