#pragma once

#include "kernel/framework/command/include_me.hpp"
#include "kernel/utility/macroses/holy_trinity.hpp"
#include <vulkan/vulkan.hpp>

#include "gpu/utils/typedef.hpp"
#include "gpu/utils/vk_converter.hpp"

namespace gpu::hard
{

class Device : public vk::PhysicalDevice, public core::CommandCaller
{
public:
    static constexpr auto CMD_DEV_PROPERTY_NAME = "eng.hard.dev_prop";

    Device(vk::PhysicalDevice& a_myself);
    HOLY_TRINITY_NOCOPY(Device);

    VK_CONVERTER(vk::PhysicalDevice);

    std::string getName() const;

    type::MemoryTypeIndex getMemoryTypeIndex(
        type::MemoryTypeBits a_type_filter,
        vk::MemoryPropertyFlags a_properties);

private:
    COMMAND_HANDLER(printFamilyProperty, 0);
};

} // namespace gpu::hard
