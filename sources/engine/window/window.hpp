#pragma once

#include <GLFW/glfw3.h>

#include "kernel/framework/variable/include_me.hpp"

namespace engine::window
{

class Window
{
public:
    Window(const core::IntVar& a_width, const core::IntVar& a_heigh);
    ~Window();

    bool isClosed();
    void poolEvents();

    // TODO: createSurface
    GLFWwindow& get();

private:
    GLFWwindow* m_window;
};

}; // namespace engine::window
