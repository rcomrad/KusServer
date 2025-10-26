#pragma once

#include <vulkan/vulkan.hpp>

#include "kernel/framework/command/include_me.hpp"

namespace engine::hard
{

class Device : public core::CommandCaller
{
public:
    static constexpr auto CMD_DEV_PROPERTY_NAME = "eng.hard.dev_prop";

    Device(vk::PhysicalDevice& a_myself);

    vk::PhysicalDevice& get();
    std::string getName() const;

private:
    vk::PhysicalDevice m_device;

    COMMAND_HANDLER(printFamilyProperty, 0);
};

} // namespace engine::hard
