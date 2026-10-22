#pragma once

#include "kernel/utility/macroses/holy_trinity.hpp"
#include "kernel/utility/type/declaration/move_monitor.hpp"
#include <vulkan/vulkan.hpp>

#include "gpu/utils/vk_converter.hpp"

namespace gpu
{

namespace logic
{
class Device;
}

namespace pipeline
{

DECLARE_UNIQUE_WRAPPER_HELPERS(ShaderModule);
class Shader : public ShaderModuleBase
{
public:
    Shader(logic::Device& a_device, std::string_view a_name);

private:
    static vk::ShaderModule create(logic::Device& a_device,
                                   std::string_view a_name);
};

} // namespace pipeline

} // namespace gpu
