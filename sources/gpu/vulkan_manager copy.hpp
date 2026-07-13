#include "kernel/framework/module/include_me.hpp"
#include "kernel/utility/type/containers/atomic_shipper.hpp"
#include "kernel/utility/type/declaration/multitype_storage.hpp"

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
    VulkanManager();

    inline window::EventCarrier& getEventCarrier()
    {
        return m_event_carrier;
    }

    inline sprite::SpriteView getSpriteView(const std::string a_name) const
    {
        return m_sprites->generateSpriteView(a_name);
    }

    std::vector<command::BaseCommand> createCommandEnv();
    std::vector<command::BaseCommand> createSpriteStorage();

    void draw();

private:
    std::shared_ptr<core::MultitypeStorage> storage;

    hard::Manager m_hard_manager;
    window::Manager m_window_manager;
    logic::Manager m_logic_manager;
    pipeline::Manager m_pipeline_manager;

    void sendCommands();
    void resize();
};

} // namespace gpu
