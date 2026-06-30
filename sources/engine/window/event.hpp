#pragma once

#include <GLFW/glfw3.h>

namespace engine::window
{

enum class EventType
{
    MousePositionEvent,
    MouseInputEvent,
    KeyInputEvent
};

struct MousePosition
{
    double x;
    double y;
    bool is_valid = false;
};

struct MouseInput
{
    int button;
    int type;
};

struct KeyInput
{
    int key;
    int type;
};

struct Event
{
    EventType type;

    union
    {
        MousePosition mousePosition;
        MouseInput mouseInput;
        KeyInput keyInput;
    };

    Event(const MousePosition& p)
        : type(EventType::MousePositionEvent), mousePosition(p)
    {
    }

    Event(const MouseInput& m) : type(EventType::MouseInputEvent), mouseInput(m)
    {
    }

    Event(const KeyInput& k) : type(EventType::KeyInputEvent), keyInput(k)
    {
    }
};

}; // namespace engine::window
