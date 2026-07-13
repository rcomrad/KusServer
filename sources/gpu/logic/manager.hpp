#pragma once

#include "gpu/command/command_pool.hpp"
#include "gpu/command/draw_command.hpp"
#include "gpu/utils/typedef.hpp"

#include "device.hpp"
#include "queue.hpp"

namespace gpu
{

namespace hard
{
class Device;
}

namespace logic
{

class Manager
{
public:
    Manager(hard::Device& a_hard_device, type::FamilyIndex a_family_index);

    command::DrawCommand& getNextDrawCommand(pipeline::SwapChain& a_swap_chain);
    void execDrawCommand(pipeline::SwapChain& a_swap_chain,
                         const command::DrawCommand& a_cmd);

    Device& getDevice();
    Queue& getQueue();
    command::CommandPool& getCommandPool();

private:
    Device m_device;
    Queue m_queue;
    command::CommandPool m_command_pool;

    std::vector<command::DrawCommand> m_commands;
};

} // namespace logic

} // namespace gpu
