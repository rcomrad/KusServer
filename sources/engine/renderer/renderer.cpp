#include "renderer.hpp"

#include "engine/window/window.hpp"

namespace kusengine
{
bool
Renderer::initRenderer(Window& window)
{
    ref_to_using_window = std::make_unique<Window>(window);

    bool success = m_instance.initInstance("some name");

    if (!success) return false;

    m_swap_chain.createSurface(window, m_instance);

    if (!success) return false;

    success = m_device.createDevice(m_instance, m_swap_chain.surface());

    if (!success) return false;

    success = m_swap_chain.initSwapChain(m_device);
    if (!success) return false;

    return true;
}

void
Renderer::render()
{
}

void
Renderer::deviceWaitIdle()
{
}

void
Renderer::draw()
{
}
}; // namespace kusengine
