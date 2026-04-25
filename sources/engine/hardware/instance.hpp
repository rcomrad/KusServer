#pragma once

#include <vulkan/vulkan.hpp>

//*************************

#include <GLFW/glfw3.h>

#include <vector>

#include "debug_callback.hpp"

namespace engine::hard
{

class Instance
{
public:
    Instance();

    std::vector<vk::PhysicalDevice> getPhysicalDevices() const;

    inline vk::Instance& get()
    {
        return *m_instance;
    }

private:
    vk::UniqueInstance m_instance;
    DebugCallback m_debug_callback;

    static vk::ApplicationInfo getAppInfo();
    static std::vector<const char*> getLayers();
    static std::vector<const char*> getExtensions();
    static std::vector<vk::ValidationFeatureEnableEXT> getFeatures();
};

} // namespace engine::hard
