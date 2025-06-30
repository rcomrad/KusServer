#include "instance.hpp"

#include <iostream>

#include "GLFW/glfw3.h"
#include "engine/render_manager/device/device.hpp"

namespace kusengine
{
namespace render
{
Instance::~Instance()
{
    dldi.vkDestroyDebugUtilsMessengerEXT(m_instance.get(), m_debug_messenger,
                                         nullptr);
}

const vk::Instance&
Instance::get() const
{
    return m_instance.get();
}

std::vector<vk::PhysicalDevice>
Instance::getAvailablePhysicalDevices() const
{
    return m_instance.get().enumeratePhysicalDevices();
}

void
Instance::create(std::string_view app_name)
{
    createInstance(app_name);

    auto vkGetInstanceProcAddr =
        dl.getProcAddress<PFN_vkGetInstanceProcAddr>("vkGetInstanceProcAddr");
    dldi.init(m_instance.get(), vkGetInstanceProcAddr);

    createDebugMessenger();
}

void
Instance::createInstance(std::string_view app_name)
{
    uint32_t version = vk::makeApiVersion(0, 1, 0, 0);

    vk::ApplicationInfo app_info = vk::ApplicationInfo(
        app_name.data(), version, "KUS_ENGINE", version, version);

    auto extensions = getExtensions();

#ifdef _DEBUG

    extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

    m_validation_layers.create();

#endif // _DEBUG

    m_validation_layers.supported(extensions);

    vk::InstanceCreateInfo instance_create_info = vk::InstanceCreateInfo(
        vk::InstanceCreateFlags(), &app_info, m_validation_layers.count(),
        m_validation_layers.data(), static_cast<uint32_t>(extensions.size()),
        extensions.data());

    m_instance = vk::createInstanceUnique(instance_create_info);
}

std::vector<const char*>
Instance::getExtensions()
{
    uint32_t ext_count;
    const char** glfw_extensions =
        glfwGetRequiredInstanceExtensions(&ext_count);

    std::vector<const char*> extensions(glfw_extensions,
                                        glfw_extensions + ext_count);

    return extensions;
}

VKAPI_ATTR VkBool32 VKAPI_CALL
debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
              VkDebugUtilsMessageTypeFlagsEXT messageType,
              const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
              void* pUserData)
{
    std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

    return VK_FALSE;
}

void
Instance::createDebugMessenger()
{
    vk::DebugUtilsMessengerCreateInfoEXT create_info =
        vk::DebugUtilsMessengerCreateInfoEXT(
            vk::DebugUtilsMessengerCreateFlagsEXT(),
            vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose |
                vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning |
                vk::DebugUtilsMessageSeverityFlagBitsEXT::eError,
            vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
                vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation |
                vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance,
            debugCallback, nullptr);

    m_debug_messenger = m_instance.get().createDebugUtilsMessengerEXT(
        create_info, nullptr, dldi);
}
}; // namespace render
}; // namespace kusengine
