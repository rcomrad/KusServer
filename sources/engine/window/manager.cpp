#include "manager.hpp"

#include "kernel/framework/include_me.hpp"

namespace engine::window
{

Manager::Manager(std::shared_ptr<core::MultitypeStorage> a_obj_ref_storage)
    : m_width("win_width", 800, 800, 1920),
      m_height("win_height", 600, 600, 1200),
      m_obj_ref_storage(a_obj_ref_storage)
{
}

void
Manager::initialize()
{
    SCOPED_TRACE_INIT("window manager");

    auto& storage = *m_obj_ref_storage;

    m_window.create(m_width, m_height);
    m_surface.create(storage.get<vk::Instance>(),
                     storage.get<vk::PhysicalDevice>(), m_window->get());
    m_characteristics.create(storage.get<vk::PhysicalDevice>(),
                             m_surface->get());

    storage.put(m_window->get());
    storage.put(m_surface->get());

    storage.put(m_characteristics->family_index);
    storage.put(m_characteristics->format);
    storage.put(m_characteristics->color_space);
    storage.put(m_characteristics->present_mode);
    storage.put(m_characteristics->capability);
    storage.put(m_characteristics->image_num);
}

} // namespace engine::window
