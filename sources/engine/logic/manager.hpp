#pragma once

#include <memory>

#include "kernel/utility/type/declaration/lifecycle_manager.hpp"
#include "kernel/utility/type/declaration/multitype_storage.hpp"

#include "device.hpp"

namespace engine::logic
{

class Manager
{
public:
    Manager(std::shared_ptr<core::MultitypeStorage> a_obj_ref_storage);

    void initialize();
    void createCommandEnv();

    void nextTick();
    std::vector<vk::UniqueCommandBuffer>& getCommandBuffers();

private:
    std::shared_ptr<core::MultitypeStorage> m_obj_ref_storage;

    // at initialize
    utils::LifecycleManager<Device> m_device;

    // at createCommandEnv
    utils::LifecycleManager<CommandPool> m_command_pool;
    utils::LifecycleManager<Queue> m_queue;
    std::vector<vk::UniqueCommandBuffer> m_command_buffers;
};

} // namespace engine::logic
