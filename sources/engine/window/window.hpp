#pragma once

#include "kernel/framework/variable/include_me.hpp"
#include "kernel/utility/type/containers/ping_pong_atomic_buffer.hpp"
#include <GLFW/glfw3.h>

#include "event.hpp"

static const char* VAR_NAME_WIDTH      = "win_width";
static const char* VAR_NAME_HEIGHT     = "win_height";
static const char* VAR_NAME_IS_RESIZED = "win_is_resized";

namespace engine::window
{

using EventCarrier = utils::PingPongAtomicBuffer<Event>;

class Window
{
public:
    Window(const core::IntVar& a_width, const core::IntVar& a_heigh);
    ~Window();

    // bool isClosed();
    void poolEvents(EventCarrier& a_event_carrier);

    // TODO: createSurface
    GLFWwindow& get();

private:
    GLFWwindow* m_window;
    static std::vector<Event> m_events_buffer;

    static void windowCloseCallback(GLFWwindow*);
    static void resizeCallback(GLFWwindow*, int a_width, int a_height);

    static void cursorPositionCallback(GLFWwindow* a_window,
                                       double a_x,
                                       double a_y);
    static void mouseButtonCallback(GLFWwindow* a_window,
                                    int a_button,
                                    int a_action,
                                    int s_mods);

    static void keyCallback(GLFWwindow* a_window,
                            int a_key,
                            int a_scancode,
                            int a_action,
                            int a_mods);

    // static std::vector<Event>& synchronizeEventBuffer(GLFWwindow* a_window);
    void synchronizeEventBuffer(EventCarrier& a_event_carrier);
};

}; // namespace engine::window
