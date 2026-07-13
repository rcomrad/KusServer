#include "shader.hpp"

#include "kernel/framework/include_me.hpp"

#include "gpu/logic/device.hpp"
#include "gpu/utils/paths.hpp"

gpu::pipeline::Shader::Shader(logic::Device& a_device, std::string_view a_name)
    : vk::ShaderModule(a_device, a_name), m_device(a_device)
{
    static is_inited = false;
    if (!is_inited)
    {
        is_inited = true;
        SCOPED_TRACE_INIT("shader module");
        KERNEL.addDataShortcut(SHADER_DIR, SHADER_DIR);
    }
}

gpu::pipeline::Shader::~Shader()
{
    m_device.destroyShaderModule(toBase());
}

vk::UniqueShaderModule
gpu::pipeline::Shader::create(logic::Device& a_device, std::string_view a_name)
{
    LOG_TRACE("Creating shader for %s file", a_name);

    vk::ShaderModuleCreateInfo info;
    auto data = KERNEL.readBinaryFile(SHADER_DIR, a_name);
    info.setCodeSize(data.size())
        .setPCode(reinterpret_cast<const uint32_t*>(data.data()));

    return a_device.createShaderModule(info);
}
