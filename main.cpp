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

void run() {
	GLFWwindow *window = initWindow();

	VkInstance instance = createVulkanInstance();

	VkSurfaceKHR surface = createSurface(window, &instance);

	VkPhysicalDevice physDev = getPhysDev(instance);

	QueueFamilyIndices inds = findQueueFamilies(physDev); //This is the second time that QueueFamilyIndices have been created for this device, I'm choosing to ignore that for now
	//const float queuePriorities = 1.0f;
	//VkDeviceQueueCreateInfo qci = createQueueCreateInfo(inds, &queuePriorities);

	//VkPhysicalDeviceFeatures physDevFeatures = createDeviceFeatures();
	//VkDeviceCreateInfo dci = createDeviceCreateInfo(&qci, 1, &physDevFeatures);

	VkDevice lDev = createLogicalDevice(physDev);

	VkQueue graphicsQueue;
	vkGetDeviceQueue(lDev, inds.graphicsFamily.value(), 0, &graphicsQueue);


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
