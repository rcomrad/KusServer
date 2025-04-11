#include "shader.hpp"

#include <fstream>
namespace kusengine
{

Shader&
Shader::getInstance()
{
    static Shader shader;
    return shader;
}

bool
Shader::compile(std::string_view file_path, std::string_view ds_folder_path)
{
    std::string command;

    std::string_view compile_program_path;
    std::string file_name;

#ifdef _WIN32
    command = std::format("{} {} -o {}{}.spv", compile_program_path, file_path,
                          ds_folder_path, file_name);
#else

#endif // _WIN32

    int err_code = 0;

    err_code = system(command.c_str());

    return err_code;
}

std::vector<char>
Shader::readFile(std::string_view file_path)
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
Shader::createShaderModule(std::string_view file_path,
                           const vk::Device& logical_device)
{
    std::vector<char>&& source_code = readFile(file_path);

    vk::ShaderModuleCreateInfo moduleInfo = {};
    moduleInfo.flags                      = vk::ShaderModuleCreateFlags();
    moduleInfo.codeSize                   = source_code.size();
    moduleInfo.pCode = reinterpret_cast<const uint32_t*>(source_code.data());

    return logical_device.createShaderModule(moduleInfo);
}
}; // namespace kusengine
