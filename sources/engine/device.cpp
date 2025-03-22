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
    VkInstance instance,
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
DestroyDebugUtilsMessengerEXT(VkInstance instance,
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

VkCommandPool
Device::getCommandPool()
{
    return m_command_pool;
}

VkSurfaceKHR
Device::surface()
{
    return m_surface;
}

SwapChainSupportDetails
Device::getSwapChainSupport()
{
    SwapChainSupportDetails details;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(m_physical_device, m_surface,
                                              &details.m_capabilities);

    uint32_t format_count;
    vkGetPhysicalDeviceSurfaceFormatsKHR(m_physical_device, m_surface,
                                         &format_count, nullptr);

    if (format_count != 0)
    {
        details.m_formats.resize(format_count);
        vkGetPhysicalDeviceSurfaceFormatsKHR(m_physical_device, m_surface,
                                             &format_count,
                                             details.m_formats.data());
    }

    uint32_t present_mode_count;
    vkGetPhysicalDeviceSurfacePresentModesKHR(m_physical_device, m_surface,
                                              &present_mode_count, nullptr);

    if (present_mode_count != 0)
    {
        details.m_present_modes.resize(present_mode_count);
        vkGetPhysicalDeviceSurfacePresentModesKHR(
            m_physical_device, m_surface, &present_mode_count,
            details.m_present_modes.data());
    }
    return details;
}

VkDevice
Device::device()
{
    return m_logical_device;
}

VkQueue
Device::graphicsQueue()
{
    return m_graphics_queue;
}

VkQueue
Device::presentQueue()
{
    return m_graphics_queue;
}

// class member functions
void
Device::initDevice(Window& window)
{
    createInstance();
    // setupDebugMessenger();
    createSurface(window);
    pickPhysicalDevice();
    createLogicalDevice();
    createCommandPool();
}

Device::~Device()
{
    vkDestroyCommandPool(m_logical_device, m_command_pool, nullptr);
    vkDestroyDevice(m_logical_device, nullptr);
}
// if (enableValidationLayers)
// {
//     DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
// }

// vkDestroySurfaceKHR(instance, surface_, nullptr);
// vkDestroyInstance(instance, nullptr);
// }

void
Device::createInstance()
{
    // if (enableValidationLayers && !checkValidationLayerSupport())
    // {
    //     throw std::exception(
    //         "validation layers requested, but not available!");
    // }

    VkApplicationInfo appInfo  = {};
    appInfo.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName   = "LittleVulkanEngine App";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName        = "KusEngine";
    appInfo.engineVersion      = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion         = VK_API_VERSION_1_0;

    auto extensions = getRequiredExtensions();

    VkInstanceCreateInfo instanceInfo{};
    instanceInfo.sType            = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceInfo.pApplicationInfo = &appInfo;
    instanceInfo.enabledExtensionCount =
        static_cast<uint32_t>(extensions.size());
    instanceInfo.ppEnabledExtensionNames = extensions.data();

    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
    m_validation_layers = {"VK_LAYER_KHRONOS_validation"};
    instanceInfo.enabledLayerCount =
        static_cast<uint32_t>(m_validation_layers.size());
    instanceInfo.ppEnabledLayerNames = m_validation_layers.data();

    populateDebugMessengerCreateInfo(debugCreateInfo);
    instanceInfo.pNext = nullptr;

    if (vkCreateInstance(&instanceInfo, nullptr, &m_instance) != VK_SUCCESS)
    {
        throw std::exception("failed to create instance!");
    }
}

void
Device::createSurface(Window& window)
{
    window.createWindowSurface(m_instance, &m_surface);
}

void
Device::pickPhysicalDevice()
{
    m_graphics_queue_index = -1;

    uint32_t gpu_count = 0;

    VkPhysicalDevice physical_device_arr[10];

    vkEnumeratePhysicalDevices(m_instance, &gpu_count, 0);

    vkEnumeratePhysicalDevices(m_instance, &gpu_count, physical_device_arr);

    for (uint32_t i = 0; i < gpu_count; ++i)
    {
        VkPhysicalDevice physical_device = physical_device_arr[i];

        uint32_t queue_family_count = 0;

        VkQueueFamilyProperties queue_props[10];

        vkGetPhysicalDeviceQueueFamilyProperties(physical_device,
                                                 &queue_family_count, 0);

        vkGetPhysicalDeviceQueueFamilyProperties(
            physical_device, &queue_family_count, queue_props);

        for (uint32_t j = 0; j < queue_family_count; ++j)
        {

            if (queue_props[j].queueFlags & VK_QUEUE_GRAPHICS_BIT)
            {
                VkBool32 surface_support = VK_FALSE;
                vkGetPhysicalDeviceSurfaceSupportKHR(
                    physical_device, j, m_surface, &surface_support);

                if (surface_support)
                {
                    m_graphics_queue_index = j;
                    m_physical_device      = physical_device;
                    break;
                }
            }
        }
    }
}

void
Device::createLogicalDevice()
{
    float queue_priority = 1.f;

    VkDeviceQueueCreateInfo queue_info{};
    queue_info.sType            = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queue_info.pQueuePriorities = &queue_priority;
    queue_info.queueFamilyIndex = m_graphics_queue_index;
    queue_info.queueCount       = 1;

    const char* swapchain_extensions[] = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};
    int swapchain_extensions_size      = 1;

    VkDeviceCreateInfo device_info{};
    device_info.sType                   = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    device_info.pQueueCreateInfos       = &queue_info;
    device_info.queueCreateInfoCount    = 1;
    device_info.enabledExtensionCount   = swapchain_extensions_size;
    device_info.ppEnabledExtensionNames = swapchain_extensions;

    vkCreateDevice(m_physical_device, &device_info, 0, &m_logical_device);

    vkGetDeviceQueue(m_logical_device, m_graphics_queue_index, 0,
                     &m_graphics_queue);
}

void
Device::createCommandPool()
{
    VkCommandPoolCreateInfo command_pool_info = {};
    command_pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    command_pool_info.queueFamilyIndex = m_graphics_queue_index;
    command_pool_info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    vkCreateCommandPool(m_logical_device, &command_pool_info, 0,
                        &m_command_pool);
}

// bool
// Device::isDeviceSuitable(Vkm_physical_device device)
// {
//     QueueFamilyIndices indices = findQueueFamilies(device);

//     bool extensionsSupported = checkDeviceExtensionSupport(device);

//     bool swapChainAdequate = false;
//     if (extensionsSupported)
//     {
//         SwapChainSupportDetails swapChainSupport =
//             querySwapChainSupport(device);
//         swapChainAdequate = !swapChainSupport.formats.empty() &&
//                             !swapChainSupport.presentModes.empty();
//     }

//     Vkm_physical_deviceFeatures supportedFeatures;
//     vkGetm_physical_deviceFeatures(device, &supportedFeatures);

//     return indices.isComplete() && extensionsSupported && swapChainAdequate
//     &&
//            supportedFeatures.samplerAnisotropy;
// }

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

// void
// Device::setupDebugMessenger()
// {
//     if (!enableValidationLayers) return;
//     VkDebugUtilsMessengerCreateInfoEXT createInfo;
//     populateDebugMessengerCreateInfo(createInfo);
//     if (CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr,
//                                      &debugMessenger) != VK_SUCCESS)
//     {
//         throw std::exception("failed to set up debug messenger!");
//     }
// }

// bool
// Device::checkValidationLayerSupport()
// {
//     uint32_t layerCount;
//     vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

//     std::vector<VkLayerProperties> availableLayers(layerCount);
//     vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

//     for (const char* layerName : validationLayers)
//     {
//         bool layerFound = false;

//         for (const auto& layerProperties : availableLayers)
//         {
//             if (strcmp(layerName, layerProperties.layerName) == 0)
//             {
//                 layerFound = true;
//                 break;
//             }
//         }

//         if (!layerFound)
//         {
//             return false;
//         }
//     }

//     return true;
// }

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

// void
// Device::hasGflwRequiredInstanceExtensions()
// {
//     uint32_t extensionCount = 0;
//     vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount,
//     nullptr); std::vector<VkExtensionProperties> extensions(extensionCount);
//     vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount,
//                                            extensions.data());

//     std::cout << "available extensions:" << std::endl;
//     std::unordered_set<std::string> available;
//     for (const auto& extension : extensions)
//     {
//         std::cout << "\t" << extension.extensionName << std::endl;
//         available.insert(extension.extensionName);
//     }

//     std::cout << "required extensions:" << std::endl;
//     auto requiredExtensions = getRequiredExtensions();
//     for (const auto& required : requiredExtensions)
//     {
//         std::cout << "\t" << required << std::endl;
//         if (available.find(required) == available.end())
//         {
//             throw std::exception("Missing required glfw extension");
//         }
//     }
// }

// bool
// Device::checkDeviceExtensionSupport(Vkm_physical_device device)
// {
//     uint32_t extensionCount;
//     vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount,
//                                          nullptr);

//     std::vector<VkExtensionProperties> availableExtensions(extensionCount);
//     vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount,
//                                          availableExtensions.data());

//     std::set<std::string> requiredExtensions(deviceExtensions.begin(),
//                                              deviceExtensions.end());

//     for (const auto& extension : availableExtensions)
//     {
//         requiredExtensions.erase(extension.extensionName);
//     }

//     return requiredExtensions.empty();
// }

// QueueFamilyIndices
// Device::findQueueFamilies(Vkm_physical_device device)
// {
//     QueueFamilyIndices indices;

//     uint32_t queueFamilyCount = 0;
//     vkGetm_physical_deviceQueueFamilyProperties(device, &queueFamilyCount,
//                                              nullptr);

//     std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
//     vkGetm_physical_deviceQueueFamilyProperties(device, &queueFamilyCount,
//                                              queueFamilies.data());

//     int i = 0;
//     for (const auto& queueFamily : queueFamilies)
//     {
//         if (queueFamily.queueCount > 0 &&
//             queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
//         {
//             indices.graphicsFamily         = i;
//             indices.graphicsFamilyHasValue = true;
//         }
//         VkBool32 presentSupport = false;
//         vkGetm_physical_deviceSurfaceSupportKHR(device, i, surface_,
//                                              &presentSupport);
//         if (queueFamily.queueCount > 0 && presentSupport)
//         {
//             indices.presentFamily         = i;
//             indices.presentFamilyHasValue = true;
//         }
//         if (indices.isComplete())
//         {
//             break;
//         }

//         i++;
//     }

//     return indices;
// }

// SwapChainSupportDetails
// Device::querySwapChainSupport(Vkm_physical_device device)
// {
//     SwapChainSupportDetails details;
//     vkGetm_physical_deviceSurfaceCapabilitiesKHR(device, surface_,
//                                               &details.capabilities);

//     uint32_t formatCount;
//     vkGetm_physical_deviceSurfaceFormatsKHR(device, surface_, &formatCount,
//                                          nullptr);

//     if (formatCount != 0)
//     {
//         details.formats.resize(formatCount);
//         vkGetm_physical_deviceSurfaceFormatsKHR(device, surface_,
//         &formatCount,
//                                              details.formats.data());
//     }

//     uint32_t presentModeCount;
//     vkGetm_physical_deviceSurfacePresentModesKHR(device, surface_,
//                                               &presentModeCount, nullptr);

//     if (presentModeCount != 0)
//     {
//         details.presentModes.resize(presentModeCount);
//         vkGetm_physical_deviceSurfacePresentModesKHR(
//             device, surface_, &presentModeCount,
//             details.presentModes.data());
//     }
//     return details;
// }

// VkFormat
// Device::findSupportedFormat(const std::vector<VkFormat>& candidates,
//                             VkImageTiling tiling,
//                             VkFormatFeatureFlags features)
// {
//     for (VkFormat format : candidates)
//     {
//         VkFormatProperties props;
//         vkGetm_physical_deviceFormatProperties(m_physical_device, format,
//         &props);

//         if (tiling == VK_IMAGE_TILING_LINEAR &&
//             (props.linearTilingFeatures & features) == features)
//         {
//             return format;
//         }
//         else if (tiling == VK_IMAGE_TILING_OPTIMAL &&
//                  (props.optimalTilingFeatures & features) == features)
//         {
//             return format;
//         }
//     }
//     throw std::exception("failed to find supported format!");
// }

uint32_t
Device::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties)
{
    VkPhysicalDeviceMemoryProperties memProperties;
    vkGetPhysicalDeviceMemoryProperties(m_physical_device, &memProperties);
    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
    {
        if ((typeFilter & (1 << i)) &&
            (memProperties.memoryTypes[i].propertyFlags & properties) ==
                properties)
        {
            return i;
        }
    }

    throw std::exception("failed to find suitable memory type!");
}

void
Device::createBuffer(VkDeviceSize size,
                     VkBufferUsageFlags usage,
                     VkMemoryPropertyFlags properties,
                     VkBuffer& buffer,
                     VkDeviceMemory& bufferMemory)
{
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType       = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size        = size;
    bufferInfo.usage       = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(m_logical_device, &bufferInfo, nullptr, &buffer) !=
        VK_SUCCESS)
    {
        throw std::exception("failed to create buffer!");
    }

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(m_logical_device, buffer, &memRequirements);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType          = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex =
        findMemoryType(memRequirements.memoryTypeBits, properties);

    if (vkAllocateMemory(m_logical_device, &allocInfo, nullptr,
                         &bufferMemory) != VK_SUCCESS)
    {
        throw std::exception("failed to allocate buffer memory!");
    }

    vkBindBufferMemory(m_logical_device, buffer, bufferMemory, 0);
}

// VkCommandBuffer
// Device::beginSingleTimeCommands()
// {
//     VkCommandBufferAllocateInfo allocInfo{};
//     allocInfo.sType       = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
//     allocInfo.level       = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
//     allocInfo.commandPool = commandPool;
//     allocInfo.commandBufferCount = 1;

//     VkCommandBuffer commandBuffer;
//     vkAllocateCommandBuffers(device_, &allocInfo, &commandBuffer);

//     VkCommandBufferBeginInfo beginInfo{};
//     beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
//     beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

//     vkBeginCommandBuffer(commandBuffer, &beginInfo);
//     return commandBuffer;
// }

// void
// Device::endSingleTimeCommands(VkCommandBuffer commandBuffer)
// {
//     vkEndCommandBuffer(commandBuffer);

//     VkSubmitInfo submitInfo{};
//     submitInfo.sType              = VK_STRUCTURE_TYPE_SUBMIT_INFO;
//     submitInfo.commandBufferCount = 1;
//     submitInfo.pCommandBuffers    = &commandBuffer;

//     vkQueueSubmit(graphicsQueue_, 1, &submitInfo, VK_NULL_HANDLE);
//     vkQueueWaitIdle(graphicsQueue_);

//     vkFreeCommandBuffers(device_, commandPool, 1, &commandBuffer);
// }

// void
// Device::copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size)
// {
//     VkCommandBuffer commandBuffer = beginSingleTimeCommands();

//     VkBufferCopy copyRegion{};
//     copyRegion.srcOffset = 0; // Optional
//     copyRegion.dstOffset = 0; // Optional
//     copyRegion.size      = size;
//     vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

//     endSingleTimeCommands(commandBuffer);
// }

// void
// Device::copyBufferToImage(VkBuffer buffer,
//                           VkImage image,
//                           uint32_t width,
//                           uint32_t height,
//                           uint32_t layerCount)
// {
//     VkCommandBuffer commandBuffer = beginSingleTimeCommands();

//     VkBufferImageCopy region{};
//     region.bufferOffset      = 0;
//     region.bufferRowLength   = 0;
//     region.bufferImageHeight = 0;

//     region.imageSubresource.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
//     region.imageSubresource.mipLevel       = 0;
//     region.imageSubresource.baseArrayLayer = 0;
//     region.imageSubresource.layerCount     = layerCount;

//     region.imageOffset = {0, 0, 0};
//     region.imageExtent = {width, height, 1};

//     vkCmdCopyBufferToImage(commandBuffer, buffer, image,
//                            VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);
//     endSingleTimeCommands(commandBuffer);
// }

// void
// Device::createImageWithInfo(const VkImageCreateInfo& imageInfo,
//                             VkMemoryPropertyFlags properties,
//                             VkImage& image,
//                             VkDeviceMemory& imageMemory)
// {
//     if (vkCreateImage(device_, &imageInfo, nullptr, &image) != VK_SUCCESS)
//     {
//         throw std::exception("failed to create image!");
//     }

//     VkMemoryRequirements memRequirements;
//     vkGetImageMemoryRequirements(device_, image, &memRequirements);

//     VkMemoryAllocateInfo allocInfo{};
//     allocInfo.sType          = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
//     allocInfo.allocationSize = memRequirements.size;
//     allocInfo.memoryTypeIndex =
//         findMemoryType(memRequirements.memoryTypeBits, properties);

//     if (vkAllocateMemory(device_, &allocInfo, nullptr, &imageMemory) !=
//         VK_SUCCESS)
//     {
//         throw std::exception("failed to allocate image memory!");
//     }

//     if (vkBindImageMemory(device_, image, imageMemory, 0) != VK_SUCCESS)
//     {
//         throw std::exception("failed to bind image memory!");
//     }
// }
}; // namespace kusengine
