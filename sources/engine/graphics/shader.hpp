#pragma once

#include <vulkan/vulkan.hpp>

namespace engine
{

class Shader
{
public:
    static void init();
    static vk::UniqueShaderModule create(vk::Device a_logic_device,
                                   std::string_view a_name);

private:
};

} // namespace engine
