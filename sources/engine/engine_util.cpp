#include <vulkan/vulkan.hpp>

#include <fstream>

#include "utility/file_system/path_storage.hpp"
namespace kusengine
{
namespace engine_util
{
std::vector<char>
readFile(std::string_view filepath)
{
    std::string full_filepath =
        util::PathStorage::getFolderPath("app").value().data();

    full_filepath += filepath.data();

    std::ifstream file{full_filepath, std::ios::ate | std::ios::binary};

    size_t fileSize = static_cast<size_t>(file.tellg());
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();
    return buffer;
}

VkDescriptorSetLayoutBinding
layout_binding(VkDescriptorType type,
               VkShaderStageFlags shaderStages,
               uint32_t count,
               uint32_t bindingNumber)
{
    VkDescriptorSetLayoutBinding binding = {};
    binding.binding                      = bindingNumber;
    binding.descriptorCount              = count;
    binding.descriptorType               = type;
    binding.stageFlags                   = shaderStages;

    return binding;
}

}; // namespace engine_util
}; // namespace kusengine
