#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <vulkan/vulkan.h>

#include <vector>

#include "window.hpp"

namespace kusengine
{

struct SwapChainSupportDetails
{
    VkSurfaceCapabilitiesKHR m_capabilities;
    std::vector<VkSurfaceFormatKHR> m_formats;
    std::vector<VkPresentModeKHR> m_present_modes;
};

// struct QueueFamilyIndices
// {
//     uint32_t graphicsFamily;
//     uint32_t presentFamily;

//     bool graphicsFamilyHasValue = false;
//     bool presentFamilyHasValue  = false;

//     bool isComplete()
//     {
//         return graphicsFamilyHasValue && presentFamilyHasValue;
//     }
// };

class Device
{
public:
    Device() = default;

    void initDevice(Window& window);

    ~Device();

    // Not copyable or movable
    Device(const Device&) = delete;

    void operator=(const Device&) = delete;

    Device(Device&&) = delete;

    Device& operator=(Device&&) = delete;

    VkCommandPool getCommandPool();

    VkDevice device();

    VkSurfaceKHR surface();

    VkQueue graphicsQueue();

    VkQueue presentQueue();

    SwapChainSupportDetails getSwapChainSupport();

    uint32_t findMemoryType(uint32_t typeFilter,
                            VkMemoryPropertyFlags properties);

    // QueueFamilyIndices findPhysicalQueueFamilies()
    // {
    //     return findQueueFamilies(physicalDevice);
    // }
    // VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates,
    //                              VkImageTiling tiling,
    //                              VkFormatFeatureFlags features);

    // // Buffer Helper Functions

    void createBuffer(VkDeviceSize size,
                      VkBufferUsageFlags usage,
                      VkMemoryPropertyFlags properties,
                      VkBuffer& buffer,
                      VkDeviceMemory& bufferMemory);

    // VkCommandBuffer beginSingleTimeCommands();
    // void endSingleTimeCommands(VkCommandBuffer commandBuffer);
    // void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize
    // size); void copyBufferToImage(VkBuffer buffer,
    //                        VkImage image,
    //                        uint32_t width,
    //                        uint32_t height,
    //                        uint32_t layerCount);

    // void createImageWithInfo(const VkImageCreateInfo& imageInfo,
    //                          VkMemoryPropertyFlags properties,
    //                          VkImage& image,
    //                          VkDeviceMemory& imageMemory);

    // VkPhysicalDeviceProperties properties;

private:
    void createInstance();
    // void setupDebugMessenger();
    void createSurface(Window& window);
    void pickPhysicalDevice();
    void createLogicalDevice();
    void createCommandPool();

    VkSurfaceKHR m_surface;
    VkInstance m_instance;
    VkPhysicalDevice m_physical_device;
    int m_graphics_queue_index;
    VkDevice m_logical_device;
    VkQueue m_graphics_queue;
    VkCommandPool m_command_pool;

    // helper functions
    bool isDeviceSuitable(VkPhysicalDevice device);

    std::vector<const char*> getRequiredExtensions();

    void populateDebugMessengerCreateInfo(
        VkDebugUtilsMessengerCreateInfoEXT& createInfo);

    // bool checkValidationLayerSupport();
    // QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

    // void hasGflwRequiredInstanceExtensions();
    // bool checkDeviceExtensionSupport(VkPhysicalDevice device);
    // SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

    // VkDebugUtilsMessengerEXT debugMessenger;
    // Window m_window;

    // VkDevice device_;
    // VkQueue graphicsQueue_;
    // VkQueue presentQueue_;

    std::vector<const char*> m_validation_layers;
    // const std::vector<const char*> deviceExtensions = {
    //     VK_KHR_SWAPCHAIN_EXTENSION_NAME};
};
}; // namespace kusengine

#endif // DEVICE_HPP
