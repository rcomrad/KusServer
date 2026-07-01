#include "one_time_command.hpp"

#include "kernel/framework/logger/basic/include_me.hpp"

gpu::command::OneTimeCommand::OneTimeCommand(logic::Device& a_device,
                                             CommandPool& a_parent,
                                             vk::CommandBuffer a_this)
    : BaseCommand(a_device, a_parent, a_this)
{
    BaseCommand::begin(vk::CommandBufferUsageFlagBits::eOneTimeSubmit);
}
