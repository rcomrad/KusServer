#pragma once

#include <GLFW/glfw3.h>

#include "kernel/framework/variable/include_me.hpp"

static const char* VAR_NAME_WIDTH      = "win_width";
static const char* VAR_NAME_HEIGHT     = "win_height";
static const char* VAR_NAME_IS_RESIZED = "win_is_resized";

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

    static void resizeCallback(GLFWwindow*, int a_width, int a_height);
};

}; // namespace engine::window
