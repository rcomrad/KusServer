#pragma once

#include "kernel/utility/macroses/holy_trinity.hpp"
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

class Shader : public vk::ShaderModule
{
public:
    Shader(logic::Device& a_device, std::string_view a_name);
    ~Shader();

    HOLY_TRINITY_ONLY_MOVE(Shader);
    VK_CONVERTER(vk::ShaderModule);

private:
    logic::Device& m_device;

    static vk::ShaderModule create(logic::Device& a_device,
                                   std::string_view a_name);
};

} // namespace pipeline

} // namespace gpu
