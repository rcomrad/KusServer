#pragma once

#include "event_types.hpp"

namespace gpu::event
{

struct Event
{
    union
    {
        MousePosition mousePosition;
        MouseInput mouseInput;
        KeyInput keyInput;
    };
    EventType type;

    Event(const MousePosition& a_event);
    Event(const MouseInput& a_event);
    Event(const KeyInput& a_event);
};

}; // namespace gpu::event
