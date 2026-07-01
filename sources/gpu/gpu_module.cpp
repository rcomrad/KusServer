#include "gpu_module.hpp"

#include "kernel/framework/include_me.hpp"

#include "gpu/utils/paths.hpp"
#include "sprite/storage_builder.hpp"
#include "utils/exception.hpp"

namespace gpu
{

auto module_name = "gpu";
REG_MODULE(module_name, gpu::GPUModule);

} // namespace gpu

gpu::GPUModule::GPUModule()
    : core::ThreadModule(module_name),
      storage(std::make_shared<core::MultitypeStorage>()),
      m_hard_manager(storage),
      m_window_manager(storage),
      m_logic_manager(storage),
      m_pipeline_manager(storage)
{
    LOG_INFO("Engine module scheduled");
}

void
gpu::GPUModule::tryDraw(sprite::SpriteViewArray&& a_objects)
{
    m_shipper.store(std::move(a_objects));
}

void
gpu::GPUModule::threadInitialize()
{
    m_hard_manager.initialize();
    m_window_manager.initialize();
    m_logic_manager.initialize();
    m_pipeline_manager.reset();
    m_commands = m_logic_manager.createCommandEnv();

    m_sprites.create(createSpriteStorage(
        m_logic_manager.getDevice(), m_logic_manager.getQueue(),
        m_logic_manager.getCommandPool(),
        m_pipeline_manager.getDescSetLayout()));
    m_sprites->resize();
}

bool
gpu::GPUModule::threadLoopBody()
{
    try
    {
        auto index = m_logic_manager.startNextTick();

        auto& cmd = m_commands.at(index); // TODO: move in logic::manager

        cmd.begin(vk::CommandBufferUsageFlagBits::eSimultaneousUse);
        m_pipeline_manager.bindToNextImage(index, cmd);

        m_shipper.load(m_objects);
        for (auto& obj : m_objects)
        {
            obj.draw(m_pipeline_manager.getLayout(), cmd);
        }

        cmd.endRenderPass();
        cmd.end();

        m_logic_manager.commitNextTick(cmd);
        m_window_manager.poolEvents(m_event_carrier);
    }
    catch (const utils::ResizeException&)
    {
        m_window_manager.recalculateCapabilities();
        m_pipeline_manager.reset();
        m_sprites->resize();
    }

    return KERNEL.getVariable("is_running");
}

void
gpu::GPUModule::threadTerminate()
{
}

gpu::sprite::SpriteStorage
gpu::GPUModule::createSpriteStorage(logic::Device& a_device,
                                    logic::Queue& a_queue,
                                    command::CommandPool& a_comm_pool,
                                    vk::DescriptorSetLayout a_desc_set_layout)
{
    KERNEL.addDataShortcut(IMAGES_DIR, IMAGES_DIR);
    auto files = KERNEL.getShortcutFileContent(IMAGES_DIR);

    sprite::StorageBuilder builder(a_device);
    for (auto path : files)
    {
        builder.push(path);
    }
    return builder.collapse(a_queue, a_comm_pool, a_desc_set_layout);
}
