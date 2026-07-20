#pragma once

#include "kernel/utility/macroses/holy_trinity.hpp"
#include "kernel/utility/type/declaration/lifecycle_manager.hpp"

#include "gpu/hardware/manager.hpp"
#include "gpu/logic/manager.hpp"
#include "gpu/window/manager.hpp"
#include "gpu/window/window.hpp"
#include "pipeline/manager.hpp"

namespace gpu
{

class VulkanManager
{
public:
    VulkanManager(hard::Manager&& a_hard_manager,
                  window::Manager&& a_window_manager,
                  logic::Manager&& a_logic_manager,
                  pipeline::Manager&& a_pipeline_manager);
    HOLY_TRINITY_ONLY_MOVE(VulkanManager);

    command::DrawCommand& getNextDrawCommand();
    void execDrawCommand(const command::DrawCommand& a_cmd);

    void poolEvents(window::EventCarrier& a_event_carrier);

    void resizeWindow();

    inline auto getLayout()
    {
        return m_pipeline_manager->getLayout();
    }

private:
    hard::Manager m_hard_manager;
    window::Manager m_window_manager;
    logic::Manager m_logic_manager;
    ::utils::LifecycleManager<pipeline::Manager> m_pipeline_manager;
};

} // namespace gpu
