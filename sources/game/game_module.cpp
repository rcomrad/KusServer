#include "game_module.hpp"

#include "kernel/framework/include_me.hpp"
#include "kernel/utility/synchronization/sleep.hpp"

#include "gpu/utils/typedef.hpp"
#include "gpu/utils/variable.hpp"

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

    // m_game_objects.emplace_back(m_gpu_module->getSprite("cakez"), 200, 300);
    // m_game_objects.emplace_back(m_gpu_module->getSprite("buttons"), -200,
    // -200); m_game_objects.emplace_back(m_gpu_module->getSprite("buttons"),
    // -200, 200);

    // m_game_objects.emplace_back(m_gpu_module->getSprite("71"), 200, 300);

    buttons.create(m_gpu_module->getSpriteView("buttons_mini"),
                   gpu::type::Dimensions(1, 3), gpu::type::NDC(0, 0),
                   gpu::type::Coordinates(0, 0));
}

#include <iostream>

bool
game::GameModule::loopBody()
{
    ::utils::Sleep::yield();

    processEvents();
    update();
    draw();

    return KERNEL.getVariable("is_running");
}

void
game::GameModule::processEvents()
{
    auto& event_carrier = m_gpu_module->getEventCarrier();
    event_carrier.acquireRead(std::move(m_events_buffer));

    for (auto& e : m_events_buffer)
    {
        switch (e.type)
        {
            case gpu::event::EventType::MousePositionEvent:
                if (e.mousePosition.is_valid)
                {
                    // std::cout << "Mouse moved: " << e.mousePosition.coord.x
                    //           << " " << e.mousePosition.coord.y << '\n';

                    buttons->update(e.mousePosition.coord);
                }
                break;

            case gpu::event::EventType::MouseInputEvent:
                // std::cout << "Button: " << e.mouseInput.button << " "
                //           << e.mouseInput.type << '\n';
                break;

            case gpu::event::EventType::KeyInputEvent:
                // std::cout << "Key: " << e.keyInput.key << " "
                //           << e.mouseInput.type << '\n';
                break;
        }
    }

    m_events_buffer.clear();
}

void
game::GameModule::update()
{
    // TODO: on;y if needed

    core::IntVar height_var(VAR_NAME_FRAME_HEIGHT);
    core::IntVar width_var(VAR_NAME_FRAME_WIDTH);

    auto height = height_var.get();
    auto width  = width_var.get();

    // m_game_objects.back().makeConsistentWithWindow(height, width);

    auto size = gpu::window::Window::getSize();
    buttons->resize(size);
}

void
game::GameModule::draw()
{
    gpu::sprite::DrawTaskArray draw_tasks;

    draw_tasks =
        m_gpu_module->writeText("Awuf!", gpu::type::Coordinates(300, 300), 0);

    // buttons->pushPresentation(draw_tasks);
    // for (auto& i : m_game_objects)
    // {
    //     draw_tasks.emplace_back(i.getPresentation());
    // }
    m_gpu_module->tryDraw(std::move(draw_tasks));
}
