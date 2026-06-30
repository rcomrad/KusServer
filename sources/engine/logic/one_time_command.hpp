#pragma once

#include <vulkan/vulkan.hpp>

#include "base_command.hpp"
#include "device.hpp"

namespace engine::logic
{

class OneTimeCommand : public BaseCommand
{
public:
    OneTimeCommand(logic::Device& a_device,
                   logic::CommandPool& a_parent,
                   vk::CommandBuffer a_this);
};

} // namespace engine::logic
