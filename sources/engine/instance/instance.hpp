#ifndef INSTANCE_HPP
#define INSTANCE_HPP

#include <vulkan/vulkan.hpp>

#include <string_view>

#include "validation_layers.hpp"

namespace kusengine
{
class Instance final
{
public:
    ~Instance();

    Instance() = default;

    bool create(std::string_view app_name);

    std::vector<vk::PhysicalDevice> getAvailablePhysicalDevices() const;

    const vk::Instance& get() const;

private:
    std::vector<const char*> getExtensions();

    bool createInstance(std::string_view app_name);

    void createDebugMessenger();

    vk::UniqueInstance m_instance;

    ValidationLayers m_validation_layers;

    vk::DispatchLoaderDynamic dldi;

    vk::DebugUtilsMessengerEXT m_debug_messenger;
};
} // namespace kusengine

#endif // INSTANCE_HPP
