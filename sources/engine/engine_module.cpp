#include "engine_module.hpp"

#include "kernel/framework/include_me.hpp"

auto module_name = "engine";
REG_MODULE(module_name, engine::EngineModule);

engine::EngineModule::EngineModule()
    : core::ThreadModule(module_name),
      storage(std::make_shared<core::MultitypeStorage>()),
      m_hard_manager(storage),
      m_window_manager(storage),
      m_logic_manager(storage),
      m_graphic_manager(storage)
{
    LOG_INFO("Engine module scheduled");
}

#include <iostream>
void
engine::EngineModule::force()
{
    std::cout << "adding engine!" << std::endl;
}

void
engine::EngineModule::threadInitialize()
{
    m_hard_manager.initialize();
    m_window_manager.initialize();
    m_logic_manager.initialize();
    m_graphic_manager.reset();
    m_commands = m_logic_manager.createCommandEnv();

    KERNEL.addDataShortcut(IMAGES_DIR, IMAGES_DIR);
    auto files = KERNEL.getShortcutFileContent(IMAGES_DIR);

    m_textures.create(m_logic_manager.getCurentDevice());
    for (auto path : files)
    {
        m_textures->push(path);
    }
    m_logic_manager.collapseImagesBuffer(*m_textures,
                                         m_graphic_manager.getDescSetLayout());
}

bool
engine::EngineModule::threadLoopBody()
{
    try
    {
        auto index = m_logic_manager.startNextTick();

        auto& cmd = m_commands.at(index);

        cmd.begin(vk::CommandBufferUsageFlagBits::eSimultaneousUse);
        m_graphic_manager.bindToNextImage(index, cmd);

        cmd.bindDescriptorSets(
            vk::PipelineBindPoint::eGraphics, m_graphic_manager.getLayout(), 0,
            {m_textures->m_textures.begin()->second.descriptor_set}, {});
        cmd.draw(6, 1, 0, 0);

        cmd.endRenderPass();
        cmd.end();

        m_logic_manager.commitNextTick(cmd);
        m_window_manager.isClosed();
    }
    catch (const logic::ResizeException&)
    {
        m_window_manager.recalculateCapabilities();
        m_graphic_manager.reset();
    }
    return true;
}

void
engine::EngineModule::threadTerminate()
{
    // m_heart.destroy();
}
