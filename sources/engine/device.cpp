#include "device.hpp"

#include <iostream>
#include <set>

#include "GLFW/glfw3.h"

namespace kusengine
{

static VKAPI_ATTR VkBool32 VKAPI_CALL
debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
              VkDebugUtilsMessageTypeFlagsEXT messageType,
              const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
              void* pUserData)
{
    std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

    return VK_FALSE;
}

VkResult
CreateDebugUtilsMessengerEXT(
    vk::Instance instance,
    const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDebugUtilsMessengerEXT* pDebugMessenger)
{
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
        instance, "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr)
    {
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    }
    else
    {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}

void
DestroyDebugUtilsMessengerEXT(vk::Instance instance,
                              VkDebugUtilsMessengerEXT debugMessenger,
                              const VkAllocationCallbacks* pAllocator)
{
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
        instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr)
    {
        func(instance, debugMessenger, pAllocator);
    }
}

vk::CommandPool
Device::getCommandPool()
{
    return m_command_pool.get();
}

vk::SurfaceKHR
Device::surface()
{
    return m_surface.get();
}

SwapChainSupportDetails
Device::getSwapChainSupport()
{
    SwapChainSupportDetails details;

    details.m_capabilities =
        m_physical_device.getSurfaceCapabilitiesKHR(m_surface.get());

    details.m_formats = m_physical_device.getSurfaceFormatsKHR(m_surface.get());

    details.m_present_modes =
        m_physical_device.getSurfacePresentModesKHR(m_surface.get());

    return details;
}

vk::Device
Device::device()
{
    return m_logical_device.get();
}

vk::Queue
Device::graphicsQueue()
{
    return m_graphics_queue;
}

vk::Queue
Device::presentQueue()
{
    return m_graphics_queue;
}

// class member functions
void
Device::initDevice(Window& window)
{
    createInstance();
    createSurface(window);
    pickPhysicalDevice();
    createLogicalDevice();
    createCommandPool();
}

void
Device::createInstance()
{

    vk::ApplicationInfo app_info;
    app_info.setPApplicationName("LittleVulkanEngine App");
    app_info.setApplicationVersion(VK_MAKE_VERSION(1, 0, 0));
    app_info.setPEngineName("KusEngine");
    app_info.setEngineVersion(VK_MAKE_VERSION(1, 0, 0));
    app_info.setApiVersion(VK_API_VERSION_1_0);

    auto extensions = getRequiredExtensions();

    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
    m_validation_layers = {"VK_LAYER_KHRONOS_validation"};

    populateDebugMessengerCreateInfo(debugCreateInfo);

    vk::InstanceCreateInfo instance_create_info;
    instance_create_info.setEnabledExtensionCount(extensions.size());
    instance_create_info.setPpEnabledExtensionNames(extensions.data());
    instance_create_info.setEnabledLayerCount(m_validation_layers.size());
    instance_create_info.setPpEnabledLayerNames(m_validation_layers.data());
    instance_create_info.setPApplicationInfo(&app_info);

    m_instance.get() = vk::createInstance(instance_create_info);
}

void
Device::createSurface(Window& window)
{
    window.createWindowSurface(m_instance, m_surface);
}

void
Device::pickPhysicalDevice()
{
    m_graphics_queue_index = -1;

    std::vector<vk::PhysicalDevice> devices =
        m_instance.get().enumeratePhysicalDevices();

    for (const auto& device : devices)
    {
        auto queue_families = device.getQueueFamilyProperties();

        for (uint32_t i = 0; i < queue_families.size(); ++i)
        {
            if (queue_families[i].queueFlags & vk::QueueFlagBits::eGraphics)
            {
                if (device.getSurfaceSupportKHR(i, m_surface.get()))
                {
                    m_graphics_queue_index = static_cast<int>(i);
                    m_physical_device      = device;
                    return;
                }
            }
        }
    }
}

void
Device::createLogicalDevice()
{
    float queue_priority = 1.0f;
    vk::DeviceQueueCreateInfo queue_create_info(
        vk::DeviceQueueCreateFlags{},                  // Flags
        static_cast<uint32_t>(m_graphics_queue_index), // Queue family index
        1,                                             // Queue count
        &queue_priority                                // Queue priorities
    );

    std::vector<const char*> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME};

    vk::PhysicalDeviceFeatures device_features = {};

    vk::DeviceCreateInfo device_create_info(
        vk::DeviceCreateFlags{},
        1,                  // Queue create info count
        &queue_create_info, // Queue create infos
        0,                  // Enabled layer count
        nullptr,            // Enabled layer names
        static_cast<uint32_t>(deviceExtensions.size()), // Extension count
        deviceExtensions.data(), // Enabled extension names
        &device_features         // Device features
    );

    m_logical_device.get() = m_physical_device.createDevice(device_create_info);

    m_graphics_queue = m_logical_device.get().getQueue(
        static_cast<uint32_t>(m_graphics_queue_index), 0);
}

void
Device::createCommandPool()
{
    vk::CommandPoolCreateInfo pool_create_info(
        vk::CommandPoolCreateFlagBits::eResetCommandBuffer, // Флаги
        static_cast<uint32_t>(
            m_graphics_queue_index) // Индекс семейства очередей
    );

    m_command_pool.get() =
        m_logical_device.get().createCommandPool(pool_create_info);
}

void
Device::populateDebugMessengerCreateInfo(
    VkDebugUtilsMessengerCreateInfoEXT& createInfo)
{
    createInfo       = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo.messageSeverity =
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                             VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                             VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    createInfo.pfnUserCallback = debugCallback;
    createInfo.pUserData       = nullptr; // Optional
}

std::vector<const char*>
Device::getRequiredExtensions()
{
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector<const char*> extensions(glfwExtensions,
                                        glfwExtensions + glfwExtensionCount);

    extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

    return extensions;
}

uint32_t
Device::findMemoryType(uint32_t type_filter, vk::MemoryPropertyFlags properties)
{
    vk::PhysicalDeviceMemoryProperties mem_properties =
        m_physical_device.getMemoryProperties();

    for (uint32_t i = 0; i < mem_properties.memoryTypeCount; i++)
    {
        if ((type_filter & (1 << i)) &&
            (mem_properties.memoryTypes[i].propertyFlags & properties) ==
                properties)
        {
            return i;
        }
    }

    throw std::exception("failed to find suitable memory type!");
}

void
Device::createBuffer(vk::DeviceSize size,
                     vk::BufferUsageFlags usage,
                     vk::MemoryPropertyFlags properties,
                     vk::Buffer& buffer,
                     vk::DeviceMemory& buffer_memory)
{

    vk::BufferCreateInfo buffer_info({},                         // Flags
                                     size,                       // Size
                                     usage,                      // Usage flags
                                     vk::SharingMode::eExclusive // Sharing mode
    );

    buffer = m_logical_device.get().createBuffer(buffer_info);

    vk::MemoryRequirements mem_requirements =
        m_logical_device.get().getBufferMemoryRequirements(buffer);

    vk::MemoryAllocateInfo alloc_info(
        mem_requirements.size,
        findMemoryType(mem_requirements.memoryTypeBits, properties));

    buffer_memory = m_logical_device.get().allocateMemory(alloc_info);

    m_logical_device.get().bindBufferMemory(buffer, buffer_memory, 0);
}

void
Device::copyBuffer(vk::Buffer src_buffer,
                   vk::Buffer dst_buffer,
                   vk::DeviceSize size)
{
    vk::CommandBufferAllocateInfo alloc_info(
        m_command_pool.get(), vk::CommandBufferLevel::ePrimary, 1);

    vk::CommandBuffer command_buffer =
        m_logical_device.get().allocateCommandBuffers(alloc_info)[0];

    vk::CommandBufferBeginInfo begin_info(
        vk::CommandBufferUsageFlagBits::eOneTimeSubmit);
    command_buffer.begin(begin_info);

    vk::BufferCopy copy_region(0,   // srcOffset
                               0,   // dstOffset
                               size // size
    );
    command_buffer.copyBuffer(src_buffer, dst_buffer, 1, &copy_region);
    command_buffer.end();

    vk::SubmitInfo submit_info(0,              // waitSemaphoreCount
                               nullptr,        // pWaitSemaphores
                               nullptr,        // pWaitDstStageMask
                               1,              // commandBufferCount
                               &command_buffer // pCommandBuffers
    );

    m_graphics_queue.submit(1, &submit_info, nullptr);
    m_graphics_queue.waitIdle();

    m_logical_device.get().freeCommandBuffers(m_command_pool.get(), 1,
                                              &command_buffer);
}

}; // namespace kusengine
