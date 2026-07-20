#include "vulkan_manager.hpp"

gpu::VulkanManager::VulkanManager(hard::Manager&& a_hard_manager,
                                  window::Manager&& a_window_manager,
                                  logic::Manager&& a_logic_manager,
                                  pipeline::Manager&& a_pipeline_manager)
    : m_hard_manager(std::move(a_hard_manager)),
      m_window_manager(std::move(a_window_manager)),
      m_logic_manager(std::move(a_logic_manager)),
      m_pipeline_manager(std::move(a_pipeline_manager))
{
}

gpu::command::DrawCommand&
gpu::VulkanManager::getNextDrawCommand()
{
    auto& swap_chain = m_pipeline_manager.getSwapChain();
    auto& cmd        = m_logic_manager.getNextDrawCommand(swap_chain);
    m_pipeline_manager.bindToNextImage(cmd);
    return cmd;
}

void
gpu::VulkanManager::execDrawCommand(const command::DrawCommand& a_cmd)
{
    auto& swap_chain = m_pipeline_manager.getSwapChain();
    return execDrawCommand.getNextDrawCommand(swap_chain, a_cmd);
}

void
gpu::GPUModule::poolEvents(window::EventCarrier& a_event_carrier)
{
    m_window_manager.poolEvents(a_event_carrier);
}

void
gpu::VulkanManager::resizeWindow()
{
    m_window_manager.recalculateCapabilities();

    auto& logic_device          = logic_manager.getDevice();
    auto& surface               = window_manager.getSurface();
    const auto& characteristics = window_manager.getCharacteristics();

    m_pipeline_manager.create(logic_device, surface, characteristics);
}
