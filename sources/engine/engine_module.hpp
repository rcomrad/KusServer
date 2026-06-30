#include "kernel/framework/module/include_me.hpp"
#include "kernel/utility/type/declaration/multitype_storage.hpp"

#include "engine/graphics/manager.hpp"
#include "engine/hardware/manager.hpp"
#include "engine/logic/images_buffer.hpp"
#include "engine/logic/manager.hpp"
#include "engine/logic/vertex_buffer.hpp"
#include "engine/window/manager.hpp"

namespace engine
{

class EngineModule : public core::ThreadModule
{
public:
    EngineModule();
    void force();

    inline window::EventCarrier& getEventCarrier()
    {
        return m_event_carrier;
    }

protected:
    void threadInitialize() override;
    bool threadLoopBody() override;
    void threadTerminate() override;

private:
    std::shared_ptr<core::MultitypeStorage> storage;

    hard::Manager m_hard_manager;
    window::Manager m_window_manager;
    logic::Manager m_logic_manager;
    graphics::Manager m_graphic_manager;

    window::EventCarrier m_event_carrier;
    std::vector<logic::BaseCommand> m_commands;
    utils::LifecycleManager<logic::ImagesBuffer> m_textures;
};

} // namespace engine
