#include "game_module.hpp"

#include "kernel/framework/include_me.hpp"

#include <iostream>

#include "engine/engine_module.hpp"

namespace game
{

auto module_name = "game";
REG_MODULE(module_name, GameModule);

GameModule::GameModule() : core::Module(module_name)
{
    std::cout << "LOL1" << std::endl;
}

void
GameModule::initialize()
{
    KERNEL.startModule("engine");
    auto& engine = KERNEL.getModuleRef<engine::EngineModule>("engine");
    engine.force();
}

bool
GameModule::loopBody()
{
    return true;
}

} // namespace game
