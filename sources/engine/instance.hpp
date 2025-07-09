#pragma once

#include <vulkan/vulkan.hpp>

#include <string_view>

#include "validation_layers.hpp"

namespace engine
{

class Instance
{
public:
    Instance();
    ~Instance();


    std::vector<vk::PhysicalDevice> getAvailablePhysicalDevices() const;

    const vk::Instance& get() const;

private:
    std::vector<const char*> getExtensions();

    void createInstance(std::string_view app_name);

    void createDebugMessenger();

    vk::UniqueInstance m_instance;

    ValidationLayers m_validation_layers;

    vk::detail::DynamicLoader dl;
    vk::detail::DispatchLoaderDynamic dldi;

    vk::DebugUtilsMessengerEXT m_debug_messenger;
};

} // namespace engine
