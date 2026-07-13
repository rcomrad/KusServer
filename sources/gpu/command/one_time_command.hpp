#pragma once

#include "base_command.hpp"

namespace gpu
{

namespace command
{

class OneTimeCommand : public BaseCommand
{
public:
    OneTimeCommand(logic::Device& a_device,
                   CommandPool& a_parent,
                   vk::CommandBuffer a_this);
};

} // namespace command

} // namespace gpu
