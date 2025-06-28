#ifndef SHADER_HPP
#define SHADER_HPP

#include <vulkan/vulkan.hpp>

#include <string_view>

namespace kusengine
{
namespace render
{
namespace shader
{

bool
compile(std::string_view file_path, std::string_view ds_folder_path);

std::vector<char>
readFile(std::string_view file_path);

vk::ShaderModule
createShaderModule(std::string_view file_path);

void
destroyShaderModule(const vk::ShaderModule& shader_module);

}; // namespace shader
}; // namespace render
}; // namespace kusengine

#endif // SHADER_HPP
