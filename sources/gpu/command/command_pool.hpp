#pragma once

#include "kernel/utility/macroses/holy_trinity.hpp"
#include <vulkan/vulkan.hpp>

#include <vector>

#include "gpu/utils/typedef.hpp"
#include "gpu/utils/vk_converter.hpp"
#include "gpu/utils/vulkan_move_monitor.hpp"

#include "base_command.hpp"
#include "draw_command.hpp"
#include "one_time_command.hpp"

namespace gpu
{

namespace logic
{
class Device;
}

namespace command
{

DECLARE_UNIQUE_WRAPPER_DEVICE_HELPERS(CommandPool);
class CommandPool : public CommandPoolBase
{
public:
    CommandPool(logic::Device& a_device, type::FamilyIndex a_family_index);

    BaseCommand alocateBuffer();
    // std::vector<BaseCommand> alocateBuffers(uint32_t a_size);
    std::vector<DrawCommand> alocateDrawBuffers(uint32_t a_size);

    OneTimeCommand alocateOneTimeCommand();

private:
    static vk::CommandPool create(logic::Device& a_device,
                                  type::FamilyIndex a_family_index);

    std::vector<vk::CommandBuffer> alocate(uint32_t a_size);
};

} // namespace command

} // namespace gpu
