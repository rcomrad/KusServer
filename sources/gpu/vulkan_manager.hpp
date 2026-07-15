#include "kernel/utility/type/declaration/lifecycle_manager.hpp"

#include <vector>

#include "gpu/hardware/manager.hpp"
#include "gpu/logic/manager.hpp"
#include "gpu/window/manager.hpp"
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

    command::DrawCommand& getNextDrawCommand();
    void execDrawCommand(const command::DrawCommand& a_cmd);

    void poolEvents(EventCarrier& a_event_carrier);

    void resizeWindow();

private:
    hard::Manager m_hard_manager;
    window::Manager m_window_manager;
    logic::Manager m_logic_manager;
    ::utils::LifecycleManager<pipeline::Manager> m_pipeline_manager;
};

} // namespace gpu
