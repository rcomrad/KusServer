#pragma once

#include <vulkan/vulkan.hpp>

#include "engine/typedef.hpp"

#include "command_pool.hpp"
#include "queue.hpp"

namespace engine::logic
{

class Device
{
public:
    Device(vk::PhysicalDevice& a_device, type::FamilyIndex a_family_index);

    vk::Device& get();

private:
    float priority = 1.0;
    vk::UniqueDevice m_device;

    vk::DeviceCreateInfo getDeviceInfo();
};

} // namespace engine::logic
