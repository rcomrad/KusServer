#include "presenter.hpp"

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
gpu::GPUModule::tryShipDrawTasks(sprite::DrawTaskArray&& a_objects);
{
    m_shipper.store(std::move(a_objects));
}

gpu::window::EventCarrier&
gpu::GPUModule::getEventCarrier()
{
    return m_event_carrier;
}

void
gpu::Presenter::sendCommands()
{
    auto& cmd = m_vulkan_manager.getNextDrawCommand();

    m_shipper.load(m_draw_tasks);
    for (auto& task : m_draw_tasks)
    {
        task.execute(*m_sprites, m_pipeline_manager.getLayout(), cmd);
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
