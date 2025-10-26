#include "device.hpp"

#include "kernel/framework/logger/basic/include_me.hpp"

namespace engine::hard
{

//------------------------------------------------------------------
//                          Base

Device::Device(vk::PhysicalDevice& a_myself)
{

    registrateBaseCommand(CMD_DEV_PROPERTY_NAME,
                          "Prints properties of selected graphics device.");

    m_device = a_myself;
}

//------------------------------------------------------------------
//                          Interface

std::string
Device::getName() const
{
    return m_device.getProperties().deviceName;
}

vk::PhysicalDevice&
Device::get()
{
    return m_device;
}

//------------------------------------------------------------------
//                          Commands

void
Device::printFamilyProperty(core::Command& a_command)
{
    a_command.noVars().noArgs();

    std::string result;
    // TODO: table
    int cnt = 1;
    for (auto& queue : m_device.getQueueFamilyProperties())
    {
        result += std::to_string(cnt++);
        result += ":\n";

        result += "\tQueue count: ";
        result += std::to_string(queue.queueCount);
        result.push_back('\n');

        result += "\tTimestamp Valid Bits: ";
        result += std::to_string(queue.timestampValidBits);
        result.push_back('\n');

        result += "\tMin Image Transfer Granularity: ";
        result += std::to_string(queue.minImageTransferGranularity.width);
        result += std::to_string(queue.minImageTransferGranularity.height);
        result += std::to_string(queue.minImageTransferGranularity.depth);
        result.push_back('\n');

        result += "\tFlags: ";
        if (queue.queueFlags & vk::QueueFlagBits::eGraphics)
        {
            result += "Graphics ";
        }
        if (queue.queueFlags & vk::QueueFlagBits::eCompute)
        {
            result += "Compute ";
        }
        if (queue.queueFlags & vk::QueueFlagBits::eTransfer)
        {
            result += "Transfer ";
        }
        if (queue.queueFlags & vk::QueueFlagBits::eSparseBinding)
        {
            result += "Sparse_Binding ";
        }
        result.push_back('\n');
    }

    LOG_CMD("%s", result);
}

} // namespace engine::hard
