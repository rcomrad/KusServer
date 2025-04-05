#ifndef APP_HPP
#define APP_HPP

#include <memory>
#include <vector>

#include "renderer.hpp"
#include "window.hpp"

namespace kusengine
{
class App final
{
public:
    App() = default;

    void initApp();

    void run();

    bool loopBody();

    static constexpr int HEIGHT = 520;

    static constexpr int WIDTH = 800;

private:
    Renderer m_renderer;

    Window m_window;

    // Time

    double getLoopTime();

    void FPSLimit(const double& loop_time);

    double m_target_frame_time;

    double m_last_time;
};
}; // namespace kusengine

#endif // APP_HPP
