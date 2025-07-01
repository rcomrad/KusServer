#ifndef INSTANCE_HPP
#define INSTANCE_HPP

#include <vulkan/vulkan.hpp>

#include <string_view>

#include "validation_layers.hpp"

namespace kusengine
{
namespace render
{
class Instance final
{
public:
    ~Instance();

    Instance() = default;

    void create(std::string_view app_name);

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
}; // namespace render
} // namespace kusengine

#endif // INSTANCE_HPP
