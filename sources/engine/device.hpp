#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <vulkan/vulkan.hpp>

#include <vector>

#include "window/window.hpp"

namespace kusengine
{

struct SwapChainSupportDetails
{
    vk::SurfaceCapabilitiesKHR m_capabilities;
    std::vector<vk::SurfaceFormatKHR> m_formats;
    std::vector<vk::PresentModeKHR> m_present_modes;
};

class Device final
{
public:
    Device() = default;

    void initDevice(Window& window);

    Device(const Device&) = delete;

    Device& operator=(const Device&) = delete;

    Device(Device&&) = delete;

    Device& operator=(Device&&) = delete;

    //

    uint32_t findMemoryType(uint32_t typeFilter,
                            vk::MemoryPropertyFlags properties);

    void createBuffer(vk::DeviceSize size,
                      vk::BufferUsageFlags usage,
                      vk::MemoryPropertyFlags properties,
                      vk::Buffer& buffer,
                      vk::DeviceMemory& bufferMemory);

    void copyBuffer(vk::Buffer src_buffer,
                    vk::Buffer dst_buffer,
                    vk::DeviceSize size);

    //
    SwapChainSupportDetails getSwapChainSupport();

    vk::CommandPool getCommandPool();

    vk::Device device();

    vk::SurfaceKHR surface();

    vk::Queue graphicsQueue();

    vk::Queue presentQueue();

private:
    void createInstance();
    // void setupDebugMessenger();
    void createSurface(Window& window);
    void pickPhysicalDevice();
    void createLogicalDevice();
    void createCommandPool();

    vk::UniqueSurfaceKHR m_surface;
    vk::UniqueInstance m_instance;
    vk::PhysicalDevice m_physical_device;
    int m_graphics_queue_index;
    vk::UniqueDevice m_logical_device;
    vk::Queue m_graphics_queue;
    vk::UniqueCommandPool m_command_pool;

    // helper functions
    bool isDeviceSuitable(vk::PhysicalDevice device);

    std::vector<const char*> getRequiredExtensions();

    void populateDebugMessengerCreateInfo(
        VkDebugUtilsMessengerCreateInfoEXT& createInfo);

    std::vector<const char*> m_validation_layers;
};
}; // namespace kusengine

#endif // DEVICE_HPP
