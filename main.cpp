#define GLFW_INCLUDE_VULKAN

#include <iostream>
#include <stdexcept>
#include <cstdlib>

#include "glfw.cpp"
#include "instance.cpp"
#include "queue.cpp"
#include "physical-device.cpp"
#include "logical-device.cpp"
#include "surface.cpp"
#include "extensions.cpp"

void run() {
	GLFWwindow *window = initWindow();
	VkInstance instance = createVulkanInstance();
	VkSurfaceKHR surface = createSurface(window, &instance);

	extNames extensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME }; //TODO verbose type, could use a typedef
	PhysicalDeviceQueueFamilyIndices devInds = createPhysDev(instance, surface, &extensions);
	VkDevice lDev = createLogicalDevice(devInds, &extensions);

	VkQueue presentQueue;
	vkGetDeviceQueue(lDev, devInds.inds.presentFamily.value(), 0, &presentQueue);

	VkQueue graphicsQueue;
	vkGetDeviceQueue(lDev, devInds.inds.graphicsFamily.value(), 0, &graphicsQueue);

	glfwRun(window);

	vkDestroyDevice(lDev, nullptr);
	vkDestroySurfaceKHR(instance, surface, nullptr);
	vkDestroyInstance(instance, nullptr);
}

int main() {
	try {
		run();
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
