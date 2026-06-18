#include "manager.hpp"

#include "kernel/framework/include_me.hpp"

namespace engine::hard
{

Manager::Manager(std::shared_ptr<core::MultitypeStorage> a_obj_ref_storage)
    : m_obj_ref_storage(a_obj_ref_storage)
{

    registrateBaseCommand("eng.hard.show_dev",
                          "Prints available graphical devices.");
    registrateBaseCommand("eng.hard.set_dev",
                          "Sets physical device for commands to use.",
                          "device_id");

    // TODO: strange thing
    // m_device_cmd_obj_ptr =
    //     KERNEL.getCallerPtrRef(Device::CMD_DEV_PROPERTY_NAME);
    // *m_device_cmd_obj_ptr = nullptr;
}

void
Manager::initialize()
{
    SCOPED_TRACE_INIT("hardware manager");

    m_instance.create();

    auto vk_devices = m_instance->getPhysicalDevices();
    m_devices.reserve(vk_devices.size());
    for (auto& device : vk_devices)
    {
        m_devices.emplace_back(device);
    }

    auto& storage = *m_obj_ref_storage;
    storage.put(*m_instance);
    storage.put(m_devices[0]);
}

Device&
Manager::getCurentDevice()
{
    return m_devices.at(0);
}

void
Manager::printDeviceInfo(core::Command& a_command)
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
Manager::setDevice(core::Command& a_command)
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

} // namespace engine::hard
