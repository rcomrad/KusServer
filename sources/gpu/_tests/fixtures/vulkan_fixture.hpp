#pragma once

#include <cstdint>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

#include <vulkan/vulkan.hpp>

#include "kernel/tester/fixture.hpp"

#include "gpu/command/command_pool.hpp"
#include "gpu/hardware/device.hpp"
#include "gpu/hardware/instance.hpp"
#include "gpu/logic/device.hpp"
#include "gpu/logic/queue.hpp"
#include "gpu/utils/typedef.hpp"

namespace kustest
{

// Creates a real Vulkan instance, a physical device wrapper, a logical device,
// a graphics queue and a command pool. Tests that do not need these objects
// should derive from Fixture instead.
class VulkanFixture : public Fixture
{
protected:
    void SetUp() override
    {
        try
        {
            m_instance = std::make_unique<gpu::hard::Instance>();
        }
        catch (const std::exception& a_error)
        {
            GTEST_SKIP() << "Vulkan instance is unavailable: " << a_error.what();
        }

        auto physical_devices = m_instance->getPhysicalDevices();
        if (physical_devices.empty())
        {
            GTEST_SKIP() << "No Vulkan physical devices found";
        }

        try
        {
            m_physical_device =
                std::make_unique<gpu::hard::Device>(physical_devices.front());

            auto families = m_physical_device->getQueueFamilyProperties();
            bool found    = false;
            for (uint32_t i = 0; i < families.size(); ++i)
            {
                if (families[i].queueCount > 0 &&
                    (families[i].queueFlags & vk::QueueFlagBits::eGraphics))
                {
                    m_family_index = i;
                    found          = true;
                    break;
                }
            }
            if (!found)
            {
                GTEST_SKIP() << "No graphics queue family found";
            }

            m_device = std::make_unique<gpu::logic::Device>(
                *m_physical_device, m_family_index);
            m_queue = std::make_unique<gpu::logic::Queue>(
                *m_device, m_family_index, 0);
            m_command_pool = std::make_unique<gpu::command::CommandPool>(
                *m_device, m_family_index);
        }
        catch (const std::exception& a_error)
        {
            GTEST_SKIP() << "Vulkan device creation failed: " << a_error.what();
        }
    }

    gpu::hard::Instance& instance()
    {
        return *m_instance;
    }

    gpu::hard::Device& physicalDevice()
    {
        return *m_physical_device;
    }

    gpu::logic::Device& device()
    {
        return *m_device;
    }

    gpu::logic::Queue& queue()
    {
        return *m_queue;
    }

    gpu::command::CommandPool& commandPool()
    {
        return *m_command_pool;
    }

    gpu::type::FamilyIndex familyIndex() const
    {
        return m_family_index;
    }

private:
    std::unique_ptr<gpu::hard::Instance> m_instance;
    std::unique_ptr<gpu::hard::Device> m_physical_device;
    std::unique_ptr<gpu::logic::Device> m_device;
    std::unique_ptr<gpu::logic::Queue> m_queue;
    std::unique_ptr<gpu::command::CommandPool> m_command_pool;
    gpu::type::FamilyIndex m_family_index{};
};

} // namespace kustest
