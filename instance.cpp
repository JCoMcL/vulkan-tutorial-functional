#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "validation.cpp"

VkApplicationInfo createAppInfo() { //TODO this could be const
	VkApplicationInfo appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Hello Triangle";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "No Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;
	return appInfo;
}

/* TODO this could also be const */
VkInstanceCreateInfo createCreateInfo(VkApplicationInfo *appInfo){
	VkInstanceCreateInfo createInfo{};

	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = appInfo;

	uint32_t glfwExtensionCount = 0;

	createInfo.ppEnabledExtensionNames = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
	createInfo.enabledExtensionCount = glfwExtensionCount;

	return createInfo;
};

VkInstance createVulkanInstance(){
	reportValidationLayerSupport();

	VkApplicationInfo appInfo = createAppInfo();
	VkInstanceCreateInfo createInfo = createCreateInfo(&appInfo);

	addEnabledValidationLayers(&createInfo);

	VkInstance instance;
	if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
		 throw std::runtime_error("failed to create instance!");
	}
	return instance;
}

