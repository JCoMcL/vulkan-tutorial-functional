#define GLFW_INCLUDE_VULKAN

// these next two includes are part of the above line and are ignored in compilation
// they are only neccesary for the language server to recognise the types
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <stdexcept>

VkSurfaceKHR createSurface(GLFWwindow *window, VkInstance *instance) {
	VkSurfaceKHR surface;
	if (glfwCreateWindowSurface(*instance, window, nullptr, &surface) != VK_SUCCESS)
		throw std::runtime_error("failed to create window surface!");
	else
		return surface;
}
