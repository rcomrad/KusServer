#include "shader.hpp"

#include "kernel/framework/include_me.hpp"

#include "gpu/logic/device.hpp"
#include "gpu/utils/paths.hpp"

gpu::pipeline::Shader::Shader(logic::Device& a_device, std::string_view a_name)
    : ShaderModuleBase(create(a_device, a_name), a_device)
{
}

void
gpu::pipeline::ShaderModuleDeleter::operator()(
    logic::Device& a_device,
    vk::ShaderModule& a_this) noexcept
{
    a_device.destroyShaderModule(a_this);
}

vk::ShaderModule
gpu::pipeline::Shader::create(logic::Device& a_device, std::string_view a_name)
{
    LOG_TRACE("Creating shader for %s file", a_name);

    vk::ShaderModuleCreateInfo info;
    auto data = KERNEL.readBinaryFile(SHADER_DIR, a_name);
    info.setCodeSize(data.size())
        .setPCode(reinterpret_cast<const uint32_t*>(data.data()));

    return a_device.createShaderModule(info);
}
