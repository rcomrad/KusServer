#pragma once

#include <GLFW/glfw3.h>

namespace gpu::event
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

}; // namespace gpu::event
