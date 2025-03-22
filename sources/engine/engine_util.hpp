#ifndef ENGINE_UTIL_HPP
#define ENGINE_UTIL_HPP
#include <vulkan/vulkan.hpp>

#include <string>
#include <vector>

namespace kusengine
{
namespace engine_util
{
std::vector<char>
readFile(std::string_view filepath);

VkDescriptorSetLayoutBinding
layout_binding(VkDescriptorType type,
               VkShaderStageFlags shaderStages,
               uint32_t count,
               uint32_t bindingNumber);
}; // namespace engine_util
}; // namespace kusengine

#endif // ENGINE_UTIL_HPP
