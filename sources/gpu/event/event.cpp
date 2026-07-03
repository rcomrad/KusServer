#include "event.hpp"

gpu::event::Event::Event(const MousePosition& a_event)
    : type(EventType::MousePositionEvent), mousePosition(a_event)
{
}

gpu::event::Event::Event(const MouseInput& a_event)
    : type(EventType::MouseInputEvent), mouseInput(a_event)
{
}

gpu::event::Event::Event(const KeyInput& a_event)
    : type(EventType::KeyInputEvent), keyInput(a_event)
{
}
