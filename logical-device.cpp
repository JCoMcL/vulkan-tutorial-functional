#include <vulkan/vulkan.h>
#include <cstdlib>
#include <stdexcept>
#include <set>
#include "queue.cpp"
#include "validation.cpp"
#include "extensions.cpp"

std::vector<VkDeviceQueueCreateInfo>  createQueueCreateInfos(QueueFamilyIndices inds, const float *queuePriorities);
VkDeviceQueueCreateInfo createQueueCreateInfo(uint32_t queueFamily, const float *queuePriorities);
VkPhysicalDeviceFeatures createDeviceFeatures();
VkDeviceCreateInfo createDeviceCreateInfo(VkDeviceQueueCreateInfo *pQCreateInfo, int qCreateInfoCount, VkPhysicalDeviceFeatures *pPhysDevFeatures,	extNames *enabledExtensions);

VkDevice createLogicalDevice(PhysicalDeviceQueueFamilyIndices devInds, extNames *extensions) {
	VkDevice device;

	const float queuePriorities = 1.0f;
	std::vector<VkDeviceQueueCreateInfo> qCreateInfos = createQueueCreateInfos(devInds.inds, &queuePriorities);
	VkPhysicalDeviceFeatures physDevFeatures = createDeviceFeatures();
	VkDeviceCreateInfo dci = createDeviceCreateInfo(
			qCreateInfos.data(),
			static_cast<uint32_t>(qCreateInfos.size()),
			&physDevFeatures,
			extensions
		);

	if (vkCreateDevice(devInds.dev, &dci, nullptr, &device) != VK_SUCCESS) {
		throw std::runtime_error("failed to create logical device!");
	}
	return device;
}

//TODO: this seems to be yet another function that may continue to grow based on the specific device requirements, there should only be one such function
std::vector<VkDeviceQueueCreateInfo>  createQueueCreateInfos(QueueFamilyIndices inds, const float *queuePriorities) {
	std::vector<VkDeviceQueueCreateInfo> qCreateInfos;
	std::set<uint32_t> uniqueQueueFamilies = {inds.graphicsFamily.value(), inds.presentFamily.value()};

	for (uint32_t qFamily : uniqueQueueFamilies)
		qCreateInfos.push_back(createQueueCreateInfo(qFamily, queuePriorities));
	return qCreateInfos;
}

VkDeviceQueueCreateInfo createQueueCreateInfo(uint32_t queueFamily, const float *queuePriorities) {
	VkDeviceQueueCreateInfo queueCreateInfo{};
	queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queueCreateInfo.queueFamilyIndex = queueFamily;
	queueCreateInfo.queueCount = 1;

	queueCreateInfo.pQueuePriorities = queuePriorities;

	return queueCreateInfo;
}

VkPhysicalDeviceFeatures createDeviceFeatures() {
	VkPhysicalDeviceFeatures devFeatures{};
	//...
	return devFeatures;
}

VkDeviceCreateInfo createDeviceCreateInfo(
		VkDeviceQueueCreateInfo *pQCreateInfo,
		int qCreateInfoCount,
		VkPhysicalDeviceFeatures *pPhysDevFeatures,
		extNames *enabledExtensions
	) {
	VkDeviceCreateInfo dci{};
	dci.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	dci.pQueueCreateInfos = pQCreateInfo;
	dci.queueCreateInfoCount = qCreateInfoCount;
	dci.pEnabledFeatures = pPhysDevFeatures;

	dci.enabledExtensionCount = static_cast<uint32_t>(enabledExtensions->size());
	dci.ppEnabledExtensionNames = enabledExtensions->data();

	if (enableValidationLayers) {
		dci.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		dci.ppEnabledLayerNames = validationLayers.data();
	} else {
		dci.enabledLayerCount = 0;
	}
	return dci;
}
