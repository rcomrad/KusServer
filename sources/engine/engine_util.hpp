#ifndef ENGINE_UTIL_HPP
#define ENGINE_UTIL_HPP
#include <vulkan/vulkan.hpp>

#include <string>
#include <vector>

struct PipelineConfigInfo;

namespace kusengine
{
namespace engine_util
{
std::vector<char>
readFile(const std::string& filepath);


vk::DescriptorSetLayoutBinding
createLayoutBinding(vk::DescriptorType type,
                    vk::ShaderStageFlags stageFlags,
                    uint32_t binding,
                    uint32_t descriptorCount              = 1,
                    const vk::Sampler* pImmutableSamplers = nullptr);
}; // namespace engine_util
}; // namespace kusengine

#endif // ENGINE_UTIL_HPP
