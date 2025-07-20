#include "instance.hpp"

#include <iostream>

#include "GLFW/glfw3.h"

engine::Instance::Instance()
{
    // TODO: use gloabal version
    uint32_t version             = vk::makeApiVersion(0, 1, 0, 0);
    vk::ApplicationInfo app_info = vk::ApplicationInfo(
        "TODO: app name", version, "KUS_ENGINE", version, version);

    auto extensions = getExtensions();
    auto layer      = getLayers();

    vk::InstanceCreateInfo create_info = vk::InstanceCreateInfo(
        vk::InstanceCreateFlags(), &app_info, layer.size(), layer.data(),
        extensions.size(), extensions.data());

    m_instance = vk::createInstanceUnique(create_info);
}

engine::Instance::~Instance()
{
}

const vk::Instance&
engine::Instance::getInstance() const
{
    return m_instance.get();
}

// std::vector<vk::PhysicalDevice>
// engine::Instance::getAvailablePhysicalDevices() const
// {
//     return m_instance.get().enumeratePhysicalDevices();
// }

std::vector<const char*>
engine::Instance::getExtensions() const
{
    uint32_t ext_count;
    const char** glfw_extensions =
        glfwGetRequiredInstanceExtensions(&ext_count);

    std::vector<const char*> extensions(glfw_extensions,
                                        glfw_extensions + ext_count);

    return extensions;
}

std::vector<const char*>
engine::Instance::getLayers() const
{
#ifndef DEBUG
    // return {"VK_LAYER_KHRONOS_validation"};
    return {};
#else
    return {};
#endif
}
