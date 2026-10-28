#pragma once

#include "gpu/hardware/device.hpp"

#include "instance.hpp"

namespace kustest
{

class PhysicalDeviceFixture : public InstanceFixture
{
protected:
    PhysicalDeviceFixture();

    gpu::hard::Device& physicalDevice()
    {
        return m_physical_device;
    }

private:
    gpu::hard::Device m_physical_device;
};

} // namespace kustest
