#pragma once

#include <GLFW/glfw3.h>

#include "gpu/utils/typedef.hpp"

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
    type::Coordinates coord = {};
    bool is_valid           = false;
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
