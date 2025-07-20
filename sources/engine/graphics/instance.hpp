#pragma once

#include <vulkan/vulkan.hpp>

#include <vector>

namespace engine
{

class Instance
{
protected:
    Instance();
    ~Instance();

    // std::vector<vk::PhysicalDevice> getAvailablePhysicalDevices() const;

    const vk::Instance& getInstance() const;

private:
    vk::UniqueInstance m_instance;

    std::vector<const char*> getExtensions() const;
    std::vector<const char*> getLayers() const;
};

} // namespace engine
