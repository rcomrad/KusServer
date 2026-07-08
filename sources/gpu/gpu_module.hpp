#include "kernel/framework/module/include_me.hpp"
#include "kernel/utility/type/containers/atomic_shipper.hpp"
#include "kernel/utility/type/declaration/multitype_storage.hpp"

#include "gpu/hardware/manager.hpp"
#include "gpu/logic/manager.hpp"
#include "gpu/window/manager.hpp"
#include "pipeline/manager.hpp"
#include "sprite/draw_task.hpp"
#include "sprite/sprite_storage.hpp"
#include "sprite/sprite_view.hpp"

namespace gpu
{

class GPUModule : public core::ThreadModule
{
public:
    GPUModule();

    inline window::EventCarrier& getEventCarrier()
    {
        return m_event_carrier;
    }

    inline sprite::SpriteView getSpriteView(const std::string a_name) const
    {
        return m_sprites->generateSpriteView(a_name);
    }

    // inline int getSpriteID(const std::string a_name) const
    // {
    //     return m_sprites->getSpriteID(a_name);
    // }
    // inline const type::CoordinateSize& getSpriteSize(int a_sprite_id) const
    // {
    //     return m_sprites->getSprite(a_sprite_id).getSize();
    // }
    // inline const type::CoordinateSize& getSpriteHitboxOffset(
    //     int a_sprite_id) const
    // {
    //     return m_sprites->getSprite(a_sprite_id).getHitboxOffset();
    // }

    void tryDraw(sprite::DrawTaskArray&& a_objects);

protected:
    void threadInitialize() override;
    bool threadLoopBody() override;
    void threadTerminate() override;

private:
    std::shared_ptr<core::MultitypeStorage> storage;

    hard::Manager m_hard_manager;
    window::Manager m_window_manager;
    logic::Manager m_logic_manager;
    pipeline::Manager m_pipeline_manager;

    window::EventCarrier m_event_carrier;
    std::vector<command::BaseCommand> m_commands;
    utils::LifecycleManager<sprite::SpriteStorage> m_sprites;

    sprite::DrawTaskArray m_draw_tasks;
    utils::AtomicShipper<sprite::DrawTaskArray> m_shipper;

    static sprite::SpriteStorage createSpriteStorage(
        logic::Device& a_device,
        logic::Queue& a_queue,
        command::CommandPool& a_comm_pool,
        vk::DescriptorSetLayout a_desc_set_layout);
};

} // namespace gpu
