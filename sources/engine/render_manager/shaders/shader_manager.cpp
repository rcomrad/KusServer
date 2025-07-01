#include "shader_manager.hpp"

#include <exception>
#include <fstream>
#include <iostream>

#include "engine/render_manager/device/device.hpp"
#include "utility/file_system/path_storage.hpp"

namespace kusengine::render
{

void
ShaderManager::setup(bool need_compile)
{
    auto shaders_folder_path = util::PathStorage::getFolderPath("shaders");

    if (need_compile)
    {
        std::unordered_map<ShaderType, std::string> shader_paths = {
            {ShaderType::DEFAULT_2D_VERTEX,
             std::format("{}{}", shaders_folder_path.value().data(),
             "spirv/default_2d_vertex_shader.vert")},
            {ShaderType::DEFAULT_FRAGMENT,
             std::format("{}{}", shaders_folder_path.value().data(),
             "spirv/default_fragment_shader.frag") },
            {ShaderType::DEFAULT_3D_VERTEX,
             std::format("{}{}", shaders_folder_path.value().data(),
             "spirv/default_3d_vertex_shader.vert")}
        };

        auto dst_folder =
            std::format("{}{}", shaders_folder_path.value(), "compiled/");
        compile(dst_folder, shader_paths);
    }
    m_shader_compiled_paths = {
        {ShaderType::DEFAULT_2D_VERTEX,
         std::format("{}{}", shaders_folder_path.value().data(),
         "compiled/default_2d_vertex_shader.vert.spv")},
        {ShaderType::DEFAULT_FRAGMENT,
         std::format("{}{}", shaders_folder_path.value().data(),
         "compiled/default_fragment_shader.frag.spv") },
        {ShaderType::DEFAULT_3D_VERTEX,
         std::format("{}{}", shaders_folder_path.value().data(),
         "compiled/default_3d_vertex_shader.vert.spv")}
    };
}

std::string_view
ShaderManager::cutSPV(const std::string& str) const
{
    std::string_view res(str);
    return res.substr(0, res.size() - 4);
}

void
ShaderManager::compile(
    const std::string& ds_folder_path,
    const std::unordered_map<ShaderType, std::string>& shader_paths)
{
    for (auto& shader_path : shader_paths)
    {
        if (compile(shader_path.second, ds_folder_path))
        {
            throw std::exception(
                (shader_path.second + " cant compile\n").c_str());
        }
    }
}

bool
ShaderManager::compile(std::string_view file_path,
                       const std::string& ds_folder_path)
{
    DECLARE_LOCAL_CONTEXT;

    std::string command;

    std::string compile_program_name =
        util::PathStorage::getFolderPath("shaders").value().data();

    compile_program_name += "spirv/glslc.exe";
    std::string file_name = util::Path::getName(file_path, LOCAL_CONTEXT);

#ifdef _WIN32
    command = std::format("{} {} -o {}{}.spv", compile_program_name, file_path,
                          ds_folder_path, file_name);

    // std::cout << command << '\n';
#else

#endif // _WIN32

    int err_code = 0;

    err_code = system(command.c_str());

    return err_code;
}

std::vector<char>
ShaderManager::readFile(const std::string& file_path) const
{
    std::ifstream file(file_path.data(), std::ios::ate | std::ios::binary);

    size_t filesize{static_cast<size_t>(file.tellg())};

    std::vector<char> buffer(filesize);
    file.seekg(0);
    file.read(buffer.data(), filesize);

    file.close();

    return buffer;
}

vk::ShaderModule
ShaderManager::createShaderModule(ShaderType sh_type) const
{
    std::vector<char>&& source_code =
        readFile(m_shader_compiled_paths.at(sh_type));

    vk::ShaderModuleCreateInfo moduleInfo = {};
    moduleInfo.flags                      = vk::ShaderModuleCreateFlags();
    moduleInfo.codeSize                   = source_code.size();
    moduleInfo.pCode = reinterpret_cast<const uint32_t*>(source_code.data());

    return render::LOGICAL_DEVICE_INSTANCE.createShaderModule(moduleInfo);
}

void
ShaderManager::destroyShaderModule(const vk::ShaderModule& shader_module) const
{
    LOGICAL_DEVICE_INSTANCE.destroyShaderModule(shader_module);
}

}; // namespace kusengine::render
