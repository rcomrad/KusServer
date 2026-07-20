#include "manager.hpp"

#include "kernel/framework/include_me.hpp"

gpu::hard::Manager::Manager()
{
    registrateBaseCommand("eng.hard.show_dev",
                          "Prints available graphical devices.");
    registrateBaseCommand("eng.hard.set_dev",
                          "Sets physical device for commands to use.",
                          "device_id");

    SCOPED_TRACE_INIT("hardware devices");

    auto vk_devices = m_instance->getPhysicalDevices();
    for (auto& device : vk_devices)
    {
        m_devices.emplace_back(device);
    }
}

void
gpu::hard::Manager::initialize()
{
}

gpu::hard::Instance&
gpu::hard::Manager::getInstance()
{
    return m_devices.at(0);
}

gpu::hard::Device&
gpu::hard::Manager::getDevice()
{
    return m_devices.at(0);
}

void
gpu::hard::Manager::printDeviceInfo(core::Command& a_command)
{
    a_command.noVars().noArgs();

    std::string result;
    for (auto& device : m_devices)
    {
        result += device.getName();
        result.push_back('\n');
    }

    LOG_CMD("%s", result);
}

void
gpu::hard::Manager::setDevice(core::Command& a_command)
{
    a_command.noVars().argCount(1);

    int num = std::stoi(a_command.arguments[0]);
    if (num < 0)
    {
        LOG_ERROR("Bad device id: %d", num);
    }
    if (num > m_devices.size())
    {
        LOG_ERROR("Device id exceeds devices count: %d > %zu", num,
                  m_devices.size());
    }

    *m_device_cmd_obj_ptr = &m_devices.at(num);

    LOG_CMD("Successfully selected device #%d for command usage", num);
}
