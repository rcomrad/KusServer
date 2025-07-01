#ifndef SHADER_HPP
#define SHADER_HPP

#include <vulkan/vulkan.hpp>

#include <string_view>
#include <unordered_map>

namespace kusengine::render
{

enum class ShaderType
{
    DEFAULT_2D_VERTEX,
    DEFAULT_FRAGMENT,
    DEFAULT_3D_VERTEX
};

class ShaderManager
{
public:
    void setup(bool need_compile);

    std::vector<char> getShaderData(ShaderType);

    vk::ShaderModule createShaderModule(ShaderType sh_type) const;

    void destroyShaderModule(const vk::ShaderModule& shader_module) const;

private:
    void compile(
        const std::string& ds_folder_path,
        const std::unordered_map<ShaderType, std::string>& shader_paths);

    bool compile(std::string_view file_path, const std::string& ds_folder_path);

    std::string_view cutSPV(const std::string& str) const;

    std::vector<char> readFile(const std::string& file_path) const;

    std::unordered_map<ShaderType, std::string> m_shader_compiled_paths;
};

}; // namespace kusengine::render

#endif // SHADER_HPP
