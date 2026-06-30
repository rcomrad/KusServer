#pragma once

#include "kernel/framework/module/include_me.hpp"

#include <vector>

#include "engine/window/event.hpp"

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
    std::vector<engine::window::Event> m_events_buffer;
};

} // namespace game
