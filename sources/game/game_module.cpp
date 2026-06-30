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
    auto& engine        = KERNEL.getModuleRef<engine::EngineModule>("engine");
    auto& event_carrier = engine.getEventCarrier();
    event_carrier.acquireRead(std::move(m_events_buffer));

    // std::cout << "SIZE: " << m_events_buffer.size() << '\n';
    for (auto& e : m_events_buffer)
    {
        switch (e.type)
        {
            case engine::window::EventType::MousePositionEvent:
                if (e.mousePosition.is_valid)
                {
                    std::cout << "Mouse moved: " << e.mousePosition.x << " "
                              << e.mousePosition.y << '\n';
                }
                break;

            case engine::window::EventType::MouseInputEvent:
                std::cout << "Button: " << e.mouseInput.button << " "
                          << e.mouseInput.type << '\n';
                break;

            case engine::window::EventType::KeyInputEvent:
                std::cout << "Key: " << e.keyInput.key << " "
                          << e.mouseInput.type << '\n';
                break;
        }
    }
    m_events_buffer.clear();

    return KERNEL.getVariable("is_running");
}

} // namespace game
