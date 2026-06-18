#pragma once

#include <vulkan/vulkan.hpp>

//*************************

#include <GLFW/glfw3.h>

#include <vector>

#include "engine/vk_converter.hpp"

#include "debug_callback.hpp"

namespace engine::hard
{

class Instance : public vk::Instance
{
public:
    Instance();
    ~Instance();

    std::vector<vk::PhysicalDevice> getPhysicalDevices() const;

    VK_CONVERTER(vk::Instance);

private:
    DebugCallback m_debug_callback;

    // static vk::UniqueInstance create();
    static vk::Instance create();

    static vk::ApplicationInfo getAppInfo();
    static std::vector<const char*> getLayers();
    static std::vector<const char*> getExtensions();
    static std::vector<vk::ValidationFeatureEnableEXT> getFeatures();
};

} // namespace engine::hard
