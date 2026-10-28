#include "physical_device.hpp"

namespace kustest
{

PhysicalDeviceFixture::PhysicalDeviceFixture()
    : m_physical_device(instance().getPhysicalDevices().front())
{
}

gpu::hard::Device&
PhysicalDeviceFixture::physicalDevice()
{
    return m_physical_device;
}

} // namespace kustest
