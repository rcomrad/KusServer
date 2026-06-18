#pragma once

#include <vulkan/vulkan.hpp>

#include <vector>

#include "engine/typedef.hpp"

#include "device.hpp"

namespace engine::logic
{

class CommandPool : public vk::CommandPool
{
public:
    CommandPool(logic::Device a_device, type::FamilyIndex a_family_index);
    ~CommandPool();

    // std::vector<vk::UniqueCommandBuffer> alocateBuffers(vk::Device a_device,
    //                                                     uint32_t a_size);
    std::vector<vk::UniqueCommandBuffer> alocateBuffers(uint32_t a_size);

private:
    logic::Device m_device;

    static vk::CommandPool create(logic::Device a_device,
                                  type::FamilyIndex a_family_index);
};

} // namespace engine::logic
