#pragma once

#include <vulkan/vulkan.hpp>

#include "engine/typedef.hpp"
#include "engine/vk_converter.hpp"
#include "kernel/framework/command/include_me.hpp"

namespace engine::hard
{

class Device : public vk::PhysicalDevice, public core::CommandCaller
{
public:
    static constexpr auto CMD_DEV_PROPERTY_NAME = "eng.hard.dev_prop";

    Device(vk::PhysicalDevice& a_myself);

    VK_CONVERTER(vk::PhysicalDevice);

    std::string getName() const;

    type::MemoryTypeIndex getMemoryTypeIndex(
        type::MemoryTypeBits a_type_filter,
        vk::MemoryPropertyFlags a_properties);

private:
    COMMAND_HANDLER(printFamilyProperty, 0);
};

} // namespace engine::hard
