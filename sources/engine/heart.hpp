#pragma once

#include <memory>

#include "engine/graphics/manager.hpp"
#include "engine/hardware/manager.hpp"
#include "engine/logic/manager.hpp"
#include "engine/window/manager.hpp"
#include "kernel/utility/type/declaration/multitype_storage.hpp"

namespace engine
{

class Heart
{
public:
    Heart();

    void loop();
    bool isClosed() const noexcept;

private:
    bool m_is_closed;
    std::shared_ptr<core::MultitypeStorage> storage;

    hard::Manager m_hard_manager;
    window::Manager m_window_manager;
    logic::Manager m_logic_manager;
    graphics::Manager m_graphic_manager;
};

} // namespace engine
