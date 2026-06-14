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
    m_graphic_manager.reset();
    m_logic_manager.createCommandEnv();

    std::vector<logic::Vertex> vertices{
        {{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
        {{1.0f, 0.5f},  {1.0f, 0.0f, 1.0f}},
        {{-0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}}
    };
    m_buffer.create(m_logic_manager.getCurentDevice(), vertices);
}

void
Heart::recordCommandBuffer(int a_image_num,
                           vk::UniqueCommandBuffer& a_command_buff)
{
    static float frame = -20;
    frame              = (frame + 0.4);
    if (frame > 10) frame -= 30;

    vk::CommandBufferBeginInfo info;
    info.setFlags(vk::CommandBufferUsageFlagBits::eSimultaneousUse);
    a_command_buff->begin(info);
    m_graphic_manager.bindToNextImage(a_image_num, *a_command_buff);
    m_buffer->bind(a_command_buff);

    // std::vector<graphics::SimplePushConstantData> push;
    // push.emplace_back();
    // push.back().offset = {-0.5f + frame * 0.02f, -0.4f + frame * 0.25f};
    // push.back().color  = {0.0f, 0.0f, 0.2f + 0.2f * frame};
    // a_command_buff->pushConstants(*m_graphic_manager.getLayout(),
    //                               vk::ShaderStageFlagBits::eVertex |
    //                                   vk::ShaderStageFlagBits::eFragment,
    //                               0, push);

    graphics::SimplePushConstantData push;
    push.offset = {-0.5f + frame * 0.02f, -0.4f + frame * 0.25f};
    push.color  = {0.0f, 0.0f, 0.0f};
    a_command_buff->pushConstants(
        *m_graphic_manager.getLayout(),
        vk::ShaderStageFlagBits::eVertex | vk::ShaderStageFlagBits::eFragment,
        0, sizeof(graphics::SimplePushConstantData), &push);

    m_buffer->draw(a_command_buff);
    a_command_buff->endRenderPass();
    a_command_buff->end();
}

void
Heart::loop()
{
    if (!m_is_closed)
    {
        try
        {
            m_logic_manager.nextTick(
                [&](int a_image_num, vk::UniqueCommandBuffer& a_command_buff)
                { this->recordCommandBuffer(a_image_num, a_command_buff); });
            m_is_closed = m_window_manager.isClosed();
        }
        catch (const logic::ResizeException&)
        {
            m_window_manager.recalculateCapabilities();
            m_graphic_manager.reset();
        }
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
