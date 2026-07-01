#pragma once

#include <vulkan/vulkan.hpp>

//*************************

#include "kernel/utility/macroses/holy_trinity.hpp"
#include <GLFW/glfw3.h>

#include <vector>

#include "gpu/utils/vk_converter.hpp"

#include "debug_callback.hpp"

namespace gpu::hard
{

class Instance : public vk::Instance
{
public:
    Instance();
    ~Instance();
    HOLY_TRINITY_NOCOPY(Instance);

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

} // namespace gpu::hard
