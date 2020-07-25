#include <vulkan/vulkan.h>
#include <cstdlib>
#include <stdexcept>
#include "queue.cpp"
#include "validation.cpp"

//I try to make it so that each cpp file has only one function which gets called by main. In this one, all functions are called by main, as a result, it's much more difficult to follow

VkDevice createLogicalDevice(VkPhysicalDevice physDev, VkDeviceCreateInfo *pDci) {
	VkDevice device;
	if (vkCreateDevice(physDev, pDci, nullptr, &device) != VK_SUCCESS) {
		throw std::runtime_error("failed to create logical device!");
	}
	return device;
}

VkDeviceQueueCreateInfo createQueueCreateInfo(QueueFamilyIndices inds, float *queuePriorities) {
	VkDeviceQueueCreateInfo queueCreateInfo{};
	queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queueCreateInfo.queueFamilyIndex = inds.graphicsFamily.value();
	queueCreateInfo.queueCount = 1;

	queueCreateInfo.pQueuePriorities = queuePriorities;

	return queueCreateInfo;
}

VkPhysicalDeviceFeatures createDeviceFeatures() {
	VkPhysicalDeviceFeatures devFeatures{};
	//...
	return devFeatures;
}

VkDeviceCreateInfo createDeviceCreateInfo(VkDeviceQueueCreateInfo *pQCreateInfo, int qCreateInfoCount, VkPhysicalDeviceFeatures *pPhysDevFeatures) {
	VkDeviceCreateInfo dci{};
	dci.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	dci.pQueueCreateInfos = pQCreateInfo;
	dci.queueCreateInfoCount = qCreateInfoCount;
	dci.pEnabledFeatures = pPhysDevFeatures;

	dci.enabledExtensionCount = 0;

	if (enableValidationLayers) {
		dci.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		dci.ppEnabledLayerNames = validationLayers.data();
	} else {
		dci.enabledLayerCount = 0;
	}
	return dci;
}
