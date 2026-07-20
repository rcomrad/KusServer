#pragma once

// #include "kernel/framework/module/include_me.hpp"
// #include "kernel/utility/type/containers/ping_pong_atomic_buffer.hpp"

// #include <vector>

// #include "gpu/event/event.hpp"
// #include "gpu/gpu_module.hpp"
// #include "objects/dynamic_object.hpp"

// #include "buttons.hpp"

#include "gpu/gpu_manager.hpp"
#include "objects/object_manager.hpp"

namespace game
{

class GameManager
{
public:
    GameManager(gpu::GPUManager& a_gpu_manager_ref);

    void tick();

private:
    gpu::GPUManager& m_gpu_manager_ref;
    obj::ObjectManager m_objects;

    // std::vector<gpu::event::Event> m_events_buffer; // TODO:

    // std::vector<obj::DynamicObject> m_game_objects;

    // utils::LifecycleManager<Buttons> buttons;

    void processEvents();
    void update();
    void draw();
};

} // namespace game
