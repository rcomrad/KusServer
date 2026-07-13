#include "draw_command.hpp"

#include "kernel/framework/logger/basic/include_me.hpp"

#include "gpu/logic/device.hpp"

gpu::command::DrawCommand::DrawCommand(logic::Device& a_device,
                                       CommandPool& a_parent,
                                       vk::CommandBuffer a_this,
                                       int a_index)
    : BaseCommand(a_device, a_parent, a_this), index(a_index)
{
    BaseCommand::begin(vk::CommandBufferUsageFlagBits::eSimultaneousUse);
}
