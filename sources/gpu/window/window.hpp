#pragma once

#include "kernel/utility/type/containers/ping_pong_atomic_buffer.hpp"
#include <GLFW/glfw3.h>

#include "gpu/event/event.hpp"
#include "gpu/utils/typedef.hpp"

namespace gpu::window
{

using EventCarrier = utils::PingPongAtomicBuffer<event::Event>;

class Window
{
public:
    Window();
    ~Window();

    void updateSize() const;
    void poolEvents(EventCarrier& a_event_carrier);

    // TODO: createSurface
    GLFWwindow& get();

    static type::CoordinateSize getSize();

private:
    GLFWwindow* m_window;
    static std::vector<event::Event> m_events_buffer;

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

    void synchronizeEventBuffer(EventCarrier& a_event_carrier);
};

}; // namespace gpu::window
