#pragma once

#include "kernel/utility/type/declaration/lifecycle_manager.hpp"
#include "kernel/utility/type/declaration/multitype_storage.hpp"

#include <memory>

#include "gpu/command/base_command.hpp"
#include "gpu/command/command_pool.hpp"

#include "device.hpp"
#include "queue.hpp"

namespace gpu::logic
{

class Manager
{
public:
    Manager(std::shared_ptr<core::MultitypeStorage> a_obj_ref_storage);

    void initialize();
    std::vector<command::BaseCommand> createCommandEnv();

    uint32_t startNextTick();
    void commitNextTick(const command::BaseCommand& a_cmd);

    Device& getDevice();
    Queue& getQueue();
    command::CommandPool& getCommandPool();

private:
    uint32_t m_index;
    std::shared_ptr<core::MultitypeStorage> m_obj_ref_storage;

    // at initialize
    utils::LifecycleManager<Device> m_device;

    // at createCommandEnv
    utils::LifecycleManager<Queue> m_queue;
    utils::LifecycleManager<command::CommandPool> m_command_pool;
};

} // namespace gpu::logic
