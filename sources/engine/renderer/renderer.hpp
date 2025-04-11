#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <mutex>

#include "engine/device/device.hpp"
#include "engine/instance/instance.hpp"

#include "swap_chain.hpp"

namespace kusengine
{

class Window;

class Renderer final
{
public:
    Renderer() = default;

    void render();

    void draw();

    bool initRenderer(Window& window);

    void deviceWaitIdle();

private:
    Instance m_instance;

    Device m_device;

    SwapChain m_swap_chain;

    std::unique_ptr<Window> ref_to_using_window;
};

}; // namespace kusengine
#endif // RENDERER_HPP
