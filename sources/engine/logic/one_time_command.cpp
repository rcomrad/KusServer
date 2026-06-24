#include "one_time_command.hpp"

#include <vector>

#include "kernel/framework/logger/basic/include_me.hpp"

namespace engine::logic
{

OneTimeCommand::OneTimeCommand(logic::Device& a_device,
                               logic::CommandPool& a_parent,
                               vk::CommandBuffer a_this)
    : BaseCommand(a_device, a_parent, a_this)
{
    BaseCommand::begin(vk::CommandBufferUsageFlagBits::eOneTimeSubmit);
}

} // namespace engine::logic
