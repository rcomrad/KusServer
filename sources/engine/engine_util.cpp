#include <vulkan/vulkan.hpp>

#include <fstream>

#include "pipeline.hpp"

namespace kusengine
{
namespace engine_util
{
std::vector<char>
readFile(const std::string& filepath)
{
    std::ifstream file{filepath.data(), std::ios::ate | std::ios::binary};

    size_t fileSize = static_cast<size_t>(file.tellg());
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();
    return buffer;
}

vk::DescriptorSetLayoutBinding
createLayoutBinding(vk::DescriptorType type,
                    vk::ShaderStageFlags stageFlags,
                    uint32_t binding,
                    uint32_t descriptorCount,
                    const vk::Sampler* pImmutableSamplers)
{
    return vk::DescriptorSetLayoutBinding()
        .setBinding(binding)
        .setDescriptorType(type)
        .setDescriptorCount(descriptorCount)
        .setStageFlags(stageFlags)
        .setPImmutableSamplers(pImmutableSamplers);
}


}; // namespace engine_util
}; // namespace kusengine
