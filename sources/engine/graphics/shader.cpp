#include "shader.hpp"

#include "kernel/framework/include_me.hpp"

#define SHADER_DIR "shaders"

namespace engine
{

void
Shader::init()
{
    SCOPED_TRACE_INIT("shader module");
    KERNEL.addDataShortcut(SHADER_DIR, SHADER_DIR);
}

vk::UniqueShaderModule
Shader::create(logic::Device a_logic_device, std::string_view a_name)
{
    LOG_TRACE("Creating shader module for %s file", a_name);

    vk::ShaderModuleCreateInfo info;

    auto data = KERNEL.readBinaryFile(SHADER_DIR, a_name);

    info.setCodeSize(data.size())
        .setPCode(reinterpret_cast<const uint32_t*>(data.data()));

    // info.setCode(data);

    return a_logic_device.createShaderModuleUnique(info);
}

} // namespace engine
