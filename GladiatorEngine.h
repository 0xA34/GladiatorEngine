#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include<iostream>
#include<stdexcept>
#include<cstdlib>
#include <vector>
#include <optional>

struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	bool isCompleted() {
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};

class GladiatorEngine {
public:
	const uint32_t WIDTH = 1280;
	const uint32_t HEIGHT = 720;
	const int MAX_FRAMES_IN_FLIGHT = 2;
	uint32_t currentFrame = 0;
	const std::vector<const char*> validationLayers = {
		"VK_LAYER_KHRONOS_validation"
	};
	const std::vector<const char*> deviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};
	void run() {
		initWindow();
		initVulkan();
		mainLoop();
		cleanUp();
		checkValidationLayerSupport();
	}
private:
	GLFWwindow* window;
	VkSurfaceKHR surface;

	VkQueue graphicsQueue;
	VkQueue presentQueue;

	VkSwapchainKHR swapChain;
	std::vector<VkImage> swapChainImages;
	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;
	std::vector<VkImageView> swapChainImageViews;

	VkPipelineLayout pipelineLayout;
	VkRenderPass renderPass;

	VkPipeline graphicsPipeline;

	VkCommandPool commandPool;
	std::vector<VkCommandBuffer> commandBuffers;

	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;

	std::vector<VkFence> inFlightFences;
	bool framebufferResized = false;

	VkInstance instance;

	VkDevice device;
	VkPhysicalDevice physicalDevice;

	VkDebugUtilsMessengerEXT debugMessenger;

	static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

	void initVulkan();
	void mainLoop();
	void cleanUp();
	void initWindow();
	void createInstance();
	void createSurface();
	void createSwapchain();
	void createImageViews();
	void createGraphicsPipeline();
	void createRenderPass();
	void createFramebuffers();
	void createCommandPool();
	void createCommandBuffer();
	void recordCommandBuffer(VkCommandBuffer, uint32_t);
	void createSyncObjects();
	void drawFrame();
	void cleanUpSwapchain();
	void recreateSwapChain();
	VkShaderModule createShaderModule(const std::vector<char>&);
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>&);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>&);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR&);
	std::vector<VkFramebuffer> swapChainFramebuffers;
	bool checkValidationLayerSupport();
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	std::vector<const char*> getRequiredExtensions();
	void setupDebugMessenger();
	void pickPhysicalDevice();
	//uint32_t findQueueFamilies(VkPhysicalDevice);
	void createLogicalDevice();
	bool isDeviceSuitable(VkPhysicalDevice);
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
	VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const
		VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT*
		pDebugMessenger);
	void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
};

#ifdef NDEBUG
const bool  enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif