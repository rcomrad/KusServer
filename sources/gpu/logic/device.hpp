#pragma once

#include "kernel/utility/macroses/holy_trinity.hpp"
#include <vulkan/vulkan.hpp>

#include "gpu/hardware/device.hpp"
#include "gpu/utils/typedef.hpp"

namespace gpu::logic
{

class Device : public vk::Device
{
public:
    Device(hard::Device& a_device, type::FamilyIndex a_family_index);
    ~Device();
    HOLY_TRINITY_NOCOPY(Device);

    type::MemoryTypeIndex getMemoryTypeIndex(
        type::MemoryTypeBits a_type_filter,
        vk::MemoryPropertyFlags a_properties) const;

private:
    float priority;
    hard::Device& m_physical_device;

    static vk::Device create(hard::Device& a_device,
                             type::FamilyIndex a_family_index,
                             float& a_priority);
    vk::DeviceCreateInfo getDeviceInfo();
};

} // namespace gpu::logic
