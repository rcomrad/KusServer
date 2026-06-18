#pragma once

#include <vulkan/vulkan.hpp>

#include "engine/hardware/device.hpp"
#include "engine/typedef.hpp"

namespace engine::logic
{

class Device : public vk::Device
{
public:
    Device(hard::Device& a_device, type::FamilyIndex a_family_index);
    ~Device();

    inline type::MemoryTypeIndex getMemoryTypeIndex(
        type::MemoryTypeBits a_type_filter,
        vk::MemoryPropertyFlags a_properties)
    {
        return m_physical_device.getMemoryTypeIndex(a_type_filter,
                                                    a_properties);
    }

private:
    float priority;
    hard::Device& m_physical_device;

    static vk::Device create(hard::Device& a_device,
                             type::FamilyIndex a_family_index,
                             float& a_priority);
    vk::DeviceCreateInfo getDeviceInfo();
};

} // namespace engine::logic
