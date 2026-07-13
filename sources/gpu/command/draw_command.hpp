#pragma once

#include "base_command.hpp"

namespace gpu::command
{

class DrawCommand : public BaseCommand
{
public:
    int index;

    DrawCommand(logic::Device& a_device,
                CommandPool& a_parent,
                vk::CommandBuffer a_this, int a_index);
};

} // namespace gpu::command
