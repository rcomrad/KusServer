#include "vulkan_manager.hpp"

gpu::GPUModule::GPUModule()
    : storage(std::make_shared<core::MultitypeStorage>()),
      m_hard_manager(storage),
      m_window_manager(storage),
      m_logic_manager(storage),
      m_pipeline_manager(storage)
{
    m_hard_manager.initialize();
    m_window_manager.initialize();
    m_logic_manager.initialize();
    m_pipeline_manager.reset();
}

std::vector<gpu::command::BaseCommand>
gpu::GPUModule::createCommandEnv()
{
    return m_logic_manager.createCommandEnv();
}

void
gpu::GPUModule::draw()
{
    try
    {
        sendCommands();
    }
    catch (const utils::ResizeException&)
    {
        LOG_INFO("Need to resize window");
        resize();
    }
}

void
gpu::GPUModule::sendCommands()
{
    auto index = m_logic_manager.startNextTick();
    auto& cmd  = m_commands.at(index); // TODO: move in logic::manager

    cmd.begin(vk::CommandBufferUsageFlagBits::eSimultaneousUse);
    m_pipeline_manager.bindToNextImage(index, cmd);

    m_shipper.load(m_draw_tasks);
    for (auto& task : m_draw_tasks)
    {
        task.execute(*m_sprites, m_pipeline_manager.getLayout(), cmd);
    }

    cmd.endRenderPass();
    cmd.end();

    m_logic_manager.commitNextTick(cmd);
}

void
gpu::GPUModule::resize()
{
    m_window_manager.recalculateCapabilities();
    m_pipeline_manager.reset();
    m_sprites->resize();
}

void
gpu::GPUModule::createSpriteStorage(logic::Device& a_device,
                                    logic::Queue& a_queue,
                                    command::CommandPool& a_comm_pool,
                                    vk::DescriptorSetLayout a_desc_set_layout)
{
    sprite::SpriteStorageBuilder builder(a_device);
    font::FontStorageBuilder font_builder(builder);
    sprite::loadAllImages(builder);
    font::loadAllFonts(font_builder);
    m_sprites.create(builder.collapse(a_queue, a_comm_pool, a_desc_set_layout));
    m_fonts.create(font_builder.collapse(*m_sprites));
}
