#include "shader.hpp"

#include <fstream>

#include "engine/render_manager/device/device.hpp"
#include "utility/file_system/path.hpp"

namespace kusengine
{
namespace render
{
bool
shader::compile(std::string_view file_path, std::string_view ds_folder_path)
{
    DECLARE_LOCAL_CONTEXT;
    std::string command;

    std::string_view compile_program_name = "glslc.exe";
    std::string file_name = util::Path::getName(file_path, LOCAL_CONTEXT);

#ifdef _WIN32
    command = std::format("{} {} -o {}{}.spv", compile_program_name, file_path,
                          ds_folder_path, file_name);
#else

#endif // _WIN32

    int err_code = 0;

    err_code = system(command.c_str());

    return err_code;
}

std::vector<char>
shader::readFile(std::string_view file_path)
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
shader::createShaderModule(std::string_view file_path)
{
    std::vector<char>&& source_code = readFile(file_path);

    vk::ShaderModuleCreateInfo moduleInfo = {};
    moduleInfo.flags                      = vk::ShaderModuleCreateFlags();
    moduleInfo.codeSize                   = source_code.size();
    moduleInfo.pCode = reinterpret_cast<const uint32_t*>(source_code.data());

    return render::LOGICAL_DEVICE_INSTANCE.createShaderModule(moduleInfo);
}

void
shader::destroyShaderModule(const vk::ShaderModule& shader_module)
{
    render::LOGICAL_DEVICE_INSTANCE.destroyShaderModule(shader_module);
}
}; // namespace render
}; // namespace kusengine
