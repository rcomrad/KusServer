#include "game_module.hpp"

#include "kernel/framework/include_me.hpp"
#include "kernel/utility/synchronization/sleep.hpp"

namespace game
{

auto module_name = "game";
REG_MODULE(module_name, game::GameModule);

} // namespace game

game::GameModule::GameModule() : core::Module(module_name)
{
    KERNEL.startModule("gpu");
}

void
game::GameModule::initialize()
{
    m_gpu_module = &(KERNEL.getModuleRef<gpu::GPUModule>("gpu"));
    m_gpu_module->waitAlive();
    m_game_manager.create(m_gpu_module->getGPUManager());
}

bool
game::GameModule::loopBody()
{
    ::utils::Sleep::yield();
    m_game_manager->tick();
    return KERNEL.getVariable("is_running");
}
