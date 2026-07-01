#pragma once

#include <vulkan/vulkan.hpp>

#include "gpu/logic/device.hpp"

#include "base_command.hpp"

namespace gpu::command
{

class OneTimeCommand : public BaseCommand
{
public:
    OneTimeCommand(logic::Device& a_device,
                   CommandPool& a_parent,
                   vk::CommandBuffer a_this);
};

} // namespace gpu::command
