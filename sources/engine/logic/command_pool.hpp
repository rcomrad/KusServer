#pragma once

#include <vulkan/vulkan.hpp>

#include <vector>

#include "engine/typedef.hpp"

#include "base_command.hpp"
#include "device.hpp"
#include "one_time_command.hpp"

namespace engine::logic
{

class CommandPool : public vk::CommandPool
{
public:
    CommandPool(logic::Device& a_device, type::FamilyIndex a_family_index);
    ~CommandPool();

    // std::vector<vk::UniqueCommandBuffer> alocateBuffers(vk::Device a_device,
    //                                                     uint32_t a_size);
    logic::BaseCommand alocateBuffer();
    std::vector<logic::BaseCommand> alocateBuffers(uint32_t a_size);

    logic::OneTimeCommand alocateOneTimeCommand();

    VK_CONVERTER(vk::CommandPool);

private:
    logic::Device& m_device;

    static vk::CommandPool create(logic::Device a_device,
                                  type::FamilyIndex a_family_index);

    std::vector<vk::CommandBuffer> alocate(uint32_t a_size);
};

} // namespace engine::logic
