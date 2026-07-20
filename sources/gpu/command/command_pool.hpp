#pragma once

#include "kernel/utility/macroses/holy_trinity.hpp"
#include <vulkan/vulkan.hpp>

#include <vector>

#include "gpu/utils/typedef.hpp"
#include "gpu/utils/vk_converter.hpp"

#include "base_command.hpp"
#include "one_time_command.hpp"

namespace gpu
{

namespace logic
{
class Device;
}

namespace command
{

class CommandPool : public vk::CommandPool
{
public:
    CommandPool(logic::Device& a_device, type::FamilyIndex a_family_index);
    ~CommandPool();
    HOLY_TRINITY_ONLY_MOVE(CommandPool);

    BaseCommand alocateBuffer();
    std::vector<BaseCommand> alocateBuffers(uint32_t a_size);

    OneTimeCommand alocateOneTimeCommand();

    VK_CONVERTER(vk::CommandPool);

private:
    logic::Device& m_device;

    static vk::CommandPool create(logic::Device& a_device,
                                  type::FamilyIndex a_family_index);

    std::vector<vk::CommandBuffer> alocate(uint32_t a_size);
};

} // namespace command

} // namespace gpu
