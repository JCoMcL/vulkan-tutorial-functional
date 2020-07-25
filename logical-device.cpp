#include <vulkan/vulkan.h>
#include <cstdlib>
#include <stdexcept>
#include "queue.cpp"
#include "validation.cpp"

VkDeviceQueueCreateInfo createQueueCreateInfo(QueueFamilyIndices inds, const float *queuePriorities);
VkPhysicalDeviceFeatures createDeviceFeatures();
VkDeviceCreateInfo createDeviceCreateInfo(VkDeviceQueueCreateInfo *pQCreateInfo, int qCreateInfoCount, VkPhysicalDeviceFeatures *pPhysDevFeatures);

VkDevice createLogicalDevice(PhysicalDeviceQueueFamilyIndices devInds) {
	VkDevice device;

	const float queuePriorities = 1.0f;
	VkDeviceQueueCreateInfo qCreateInfo = createQueueCreateInfo(devInds.inds, &queuePriorities);
	VkPhysicalDeviceFeatures physDevFeatures = createDeviceFeatures();
	VkDeviceCreateInfo dci = createDeviceCreateInfo(&qCreateInfo, 1, &physDevFeatures);

	if (vkCreateDevice(devInds.dev, &dci, nullptr, &device) != VK_SUCCESS) {
		throw std::runtime_error("failed to create logical device!");
	}
	return device;
}

VkDeviceQueueCreateInfo createQueueCreateInfo(QueueFamilyIndices inds, const float *queuePriorities) {
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
