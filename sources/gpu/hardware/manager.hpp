#pragma once

#include "kernel/framework/command/include_me.hpp"
#include "kernel/utility/macroses/holy_trinity.hpp"

#include <deque>

#include "device.hpp"
#include "instance.hpp"

namespace gpu::hard
{

class Manager : public core::CommandCaller
{
public:
    Manager();
    HOLY_TRINITY_ONLY_MOVE(Manager);

    Instance& getInstance();
    Device& getDevice();

private:
    core::CommandCaller** m_device_cmd_obj_ptr;

    Instance m_instance;
    std::deque<Device> m_devices;

    COMMAND_HANDLER(printDeviceInfo, 0);
    COMMAND_HANDLER(setDevice, 1);
};

} // namespace gpu::hard
