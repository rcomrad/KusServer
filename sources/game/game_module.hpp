#pragma once

#include "kernel/framework/module/include_me.hpp"
#include "kernel/utility/type/containers/ping_pong_atomic_buffer.hpp"

#include <vector>

#include "gpu/event/event.hpp"
#include "gpu/gpu_module.hpp"
#include "objects/dynamic_object.hpp"

#include "buttons.hpp"

namespace game
{

class GameModule : public core::Module
{
public:
    GameModule();

protected:
    void initialize() override;
    bool loopBody() override;

private:
    gpu::GPUModule* m_gpu_module;

    std::vector<gpu::event::Event> m_events_buffer; // TODO:

    std::vector<obj::DynamicObject> m_game_objects;

    utils::LifecycleManager<Buttons> buttons;

    void processEvents();
    void update();
    void draw();
};

} // namespace game
