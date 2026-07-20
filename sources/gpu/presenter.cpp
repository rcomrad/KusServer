#include "presenter.hpp"

#include "gpu/utils/exception.hpp"
#include "gpu/window/window.hpp"

#include "gpu_manager.hpp"

gpu::Presenter::Presenter(VulkanManager&& a_vulkan_manager)
    : m_vulkan_manager(std::move(a_vulkan_manager))
{
}

void
gpu::Presenter::draw()
{
    try
    {
        sendCommands();
    }
    catch (const utils::ResizeException&)
    {
        resize();
    }
}

void
gpu::Presenter::tryShipDrawTasks(sprite::DrawTaskArray&& a_objects)
{
    m_shipper.store(std::move(a_objects));
}

void
gpu::Presenter::poolEvents()
{
    m_vulkan_manager.poolEvents(m_event_carrier);
}

gpu::window::EventCarrier&
gpu::Presenter::getEventCarrier()
{
    return m_event_carrier;
}

void
gpu::Presenter::sendCommands()
{
    auto window_size    = window::Window::getSize();
    const auto& storage = *static_cast<sprite::SpriteStorage*>(
        static_cast<ResourceStorage*>(static_cast<GPUManager*>(this)));
    auto& cmd = m_vulkan_manager.getNextDrawCommand();

    m_shipper.load(m_draw_tasks);
    for (auto& task : m_draw_tasks)
    {
        task.execute(storage, m_vulkan_manager.getLayout(), cmd, window_size);
    }

    cmd.endRenderPass();
    cmd.end();

    m_vulkan_manager.execDrawCommand(cmd);
}

void
gpu::Presenter::resize()
{
    LOG_INFO("Need to resize window");
    m_vulkan_manager.resizeWindow();
    m_sprites->resize();
}
