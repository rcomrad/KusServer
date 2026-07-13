#include "gpu_classes_builder.hpp"

#include "font/font_loader.hpp"
#include "font/font_storage.hpp"
#include "font/font_storage_builder.hpp"
#include "hardware/manager.hpp"
#include "logic/manager.hpp"
#include "pipeline/manager.hpp"
#include "sprite/image_loader.hpp"
#include "sprite/sprite_storage.hpp"
#include "sprite/storage_builder.hpp"
#include "window/manager.hpp"

gpu::buildGpuClasses()
{
    //*************************************
    // Vulkan manafers
    //*************************************

    hard::Manager hard_manager;

    auto& instance    = hard_manager.getInstance();
    auto& hard_device = hard_manager.getDevice();
    window::Manager window_manager(instance, hard_device);

    const auto& characteristics = window_manager.getCharacteristics();
    logic::Manager logic_manager(hard_device, characteristics.family_index);

    auto& logic_device = logic_manager.getDevice();
    auto& surface      = window_manager.getSurface();
    pipeline::Manager pipeline_manager(logic_device, surface, characteristics);

    //*************************************
    // Storages
    //*************************************

    sprite::SpriteStorageBuilder sprite_builder(logic_device);
    font::FontStorageBuilder font_builder(sprite_builder);

    sprite::loadAllImages(sprite_builder);
    font::loadAllFonts(font_builder);

    auto& queue           = m_logic_manager.getQueue();
    auto& cmd_pool        = m_logic_manager.getCommandPool();
    auto& desc_set_layout = m_pipeline_manager.getDescSetLayout();

    auto sprite_storage = builder.collapse(queue, cmd_pool, desc_set_layout);
    auto font_storage   = font_builder.collapse(sprite_storage);

    //*************************************
    // Construct global manager
    //*************************************
}
std::vector<gpu::command::BaseCommand>
gpu::GPUModule::createCommandEnv()
{
    return
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
