#pragma once

#include "kernel/framework/command/include_me.hpp"
#include "kernel/utility/type/declaration/lifecycle_manager.hpp"
#include "kernel/utility/type/declaration/multitype_storage.hpp"

#include <deque>

#include "device.hpp"
#include "instance.hpp"

namespace gpu::hard
{

class Manager : public core::CommandCaller
{
public:
    Manager(std::shared_ptr<core::MultitypeStorage> a_obj_ref_storage);

    void initialize();
    Device& getCurentDevice();

private:
    core::CommandCaller** m_device_cmd_obj_ptr;
    std::shared_ptr<core::MultitypeStorage> m_obj_ref_storage;

    utils::LifecycleManager<Instance> m_instance;
    std::deque<Device> m_devices;

    COMMAND_HANDLER(printDeviceInfo, 0);
    COMMAND_HANDLER(setDevice, 1);
};

} // namespace gpu::hard
