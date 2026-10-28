#pragma once

#include "kernel/tester/fixture.hpp"
#include <vulkan/vulkan.hpp>

#include "gpu/hardware/instance.hpp"

namespace kustest
{

class InstanceFixture : public Fixture
{
protected:
    gpu::hard::Instance& instance();

private:
    gpu::hard::Instance m_instance;
};

} // namespace kustest
