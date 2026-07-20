#include "gpu_module.hpp"

#include "kernel/framework/include_me.hpp"
#include "kernel/utility/synchronization/sleep.hpp"

#include "gpu_classes_builder.hpp"

namespace gpu
{

auto module_name = "gpu";
REG_MODULE(module_name, gpu::GPUModule);

} // namespace gpu

gpu::GPUModule::GPUModule() : core::ThreadModule(module_name)
{
    LOG_INFO("Engine module scheduled");
}

gpu::GPUManager&
gpu::GPUModule::getGPUManager()
{
    return *m_manager;
}

void
gpu::GPUModule::threadInitialize()
{
    SCOPED_TRACE_INIT("gpu module");
    m_manager.create(buildGpuClasses());
}

bool
gpu::GPUModule::threadLoopBody()
{
    ::utils::Sleep::yield();

    m_manager->draw();
    m_manager->poolEvents();

    return KERNEL.getVariable("is_running");
}

void
gpu::GPUModule::threadTerminate()
{
}
