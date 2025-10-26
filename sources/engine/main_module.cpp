#include "main_module.hpp"

#include "kernel/framework/include_me.hpp"

auto module_name = "engine";
REG_MODULE(module_name, engine::MainModule);
engine::MainModule::MainModule() : core::ThreadModule(module_name)
{
    LOG_INFO("Engine module scheduled");
}

void
engine::MainModule::threadInitialize()
{
    m_heart.create();
}

bool
engine::MainModule::threadLoopBody()
{
    m_heart.obj.loop();
    return !m_heart->isClosed();
}

void
engine::MainModule::threadTerminate()
{
    m_heart.destroy();
}
