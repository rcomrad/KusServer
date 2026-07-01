#pragma once

#include <vulkan/vulkan.hpp>

#include "gpu/logic/device.hpp"

namespace gpu::pipeline
{

class Shader
{
public:
    static void init();
    static vk::UniqueShaderModule create(logic::Device& a_logic_device,
                                         std::string_view a_name);

private:
};

} // namespace gpu::pipeline
