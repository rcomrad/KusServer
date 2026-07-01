#include "instance.hpp"

#include <GLFW/glfw3.h>

gpu::hard::Instance::Instance() : vk::Instance(create())
{
    m_debug_callback.subscribe(*this);
}

gpu::hard::Instance::~Instance()
{
    // TODO:
    // vk::destroyInstance(toBase());
    // vkDestroyInstance(toBase());
}

vk::Instance
gpu::hard::Instance::create()
{
    SCOPED_TRACE_INIT("vulkan instance");

    auto app_info   = getAppInfo();
    auto layers     = getLayers();
    auto extensions = getExtensions();
    auto features   = getFeatures();

    vk::ValidationFeaturesEXT validation;
    validation.setEnabledValidationFeatures(features);

    vk::InstanceCreateInfo info;
    info.setPApplicationInfo(&app_info)
        .setPEnabledLayerNames(layers)
        .setPEnabledExtensionNames(extensions)
        .setPNext(&validation);

    return vk::createInstance(info);
}

std::vector<vk::PhysicalDevice>
gpu::hard::Instance::getPhysicalDevices() const
{
    return this->enumeratePhysicalDevices();
}

vk::ApplicationInfo
gpu::hard::Instance::getAppInfo()
{
    vk::ApplicationInfo info;
    info.setApiVersion(VK_API_VERSION_1_4)
        .setPApplicationName("Lampa")
        .setApplicationVersion(VK_MAKE_API_VERSION(0, 1, 0, 0))
        .setPEngineName("KusEngine")
        .setEngineVersion(VK_MAKE_API_VERSION(0, 1, 0, 0));
    return info;
}

std::vector<const char*>
gpu::hard::Instance::getLayers()
{
    return {"VK_LAYER_KHRONOS_validation"};
}

std::vector<const char*>
gpu::hard::Instance::getExtensions()
{
    // TODO: optional glfw
    glfwInit();

    uint32_t ext_count;
    const char** glfw_extensions =
        glfwGetRequiredInstanceExtensions(&ext_count);

    std::vector<const char*> extensions(glfw_extensions,
                                        glfw_extensions + ext_count);

    extensions.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

    return extensions;
}

std::vector<vk::ValidationFeatureEnableEXT>
gpu::hard::Instance::getFeatures()
{
    std::vector<vk::ValidationFeatureEnableEXT> features = {
        vk::ValidationFeatureEnableEXT::eGpuAssisted,
        vk::ValidationFeatureEnableEXT::eBestPractices,
        vk::ValidationFeatureEnableEXT::eSynchronizationValidation};
    return features;
}
