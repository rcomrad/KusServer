#pragma once

#include <vulkan/vulkan.hpp>

#include <vector>

#include "engine/typedef.hpp"

namespace engine::logic
{

class CommandPool
{
public:
    CommandPool(vk::Device a_device, type::FamilyIndex a_family_index);
    std::vector<vk::UniqueCommandBuffer> alocateBuffers(vk::Device a_device,
                                                        uint32_t a_size);

private:
    vk::UniqueCommandPool m_command_pool;
};

} // namespace engine::logic
