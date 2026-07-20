#pragma once

#include "kernel/utility/macroses/holy_trinity.hpp"
#include "kernel/utility/type/containers/atomic_shipper.hpp"

#include "sprite/draw_task.hpp"

#include "vulkan_manager.hpp"

namespace gpu
{

class Presenter
{
public:
    Presenter(VulkanManager&& a_vulkan_manager);
    HOLY_TRINITY_ONLY_MOVE(Presenter);

    void draw();
    void tryShipDrawTasks(sprite::DrawTaskArray&& a_objects);

    void poolEvents();

    window::EventCarrier& getEventCarrier();

private:
    VulkanManager m_vulkan_manager;

    window::EventCarrier m_event_carrier;

    sprite::DrawTaskArray m_draw_tasks;
    utils::AtomicShipper<sprite::DrawTaskArray> m_shipper;

    void sendCommands();
    void resize();
};

} // namespace gpu
