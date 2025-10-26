#include "heart.hpp"

#include "kernel/framework/include_me.hpp"

namespace engine
{

Heart::Heart()
    : m_is_closed(false),
      storage(std::make_shared<core::MultitypeStorage>()),
      m_hard_manager(storage),
      m_window_manager(storage),
      m_logic_manager(storage),
      m_graphic_manager(storage)
{
    m_hard_manager.initialize();
    m_window_manager.initialize();
    m_logic_manager.initialize();
    m_graphic_manager.initialize();
    m_logic_manager.createCommandEnv();

    for (auto& cmd : m_logic_manager.getCommandBuffers())
    {
        vk::CommandBufferBeginInfo info;
        info.setFlags(vk::CommandBufferUsageFlagBits::eSimultaneousUse);
        cmd->begin(info);

        m_graphic_manager.bindToNextImage(*cmd);
        cmd->draw(3, 1, 0, 0);

        cmd->endRenderPass();
        cmd->end();
    }
}

void
Heart::loop()
{
    if (!m_is_closed)
    {
        m_logic_manager.nextTick();
        m_is_closed = m_window_manager.isClosed();
    }
    else
    {
        THROW("window already closed");
    }
}

bool
Heart::isClosed() const noexcept
{
    return m_is_closed;
}

} // namespace engine
