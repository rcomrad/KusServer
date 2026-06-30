#include "manager.hpp"

#include "kernel/framework/include_me.hpp"

namespace engine::window
{

Manager::Manager(std::shared_ptr<core::MultitypeStorage> a_obj_ref_storage)
    : m_width(VAR_NAME_WIDTH, 800, 10, 1920),
      m_height(VAR_NAME_HEIGHT, 600, 10, 1200),
      m_is_window_resized(VAR_NAME_IS_RESIZED, false),
      m_obj_ref_storage(a_obj_ref_storage)
{
}

void
Manager::recalculateCapabilities()
{
    auto& storage = *m_obj_ref_storage;
    m_characteristics.create(storage.get<hard::Device>(), m_surface->get());

    storage.reset(m_characteristics->family_index);
    storage.reset(m_characteristics->format);
    storage.reset(m_characteristics->color_space);
    storage.reset(m_characteristics->present_mode);
    storage.reset(m_characteristics
                      ->capability); // TODO: possably need to reset only this
    storage.reset(m_characteristics->image_num);
}

void
Manager::initialize()
{
    SCOPED_TRACE_INIT("window manager");

    auto& storage = *m_obj_ref_storage;

    m_window.create(m_width, m_height);
    m_surface.create(storage.get<hard::Instance>(), storage.get<hard::Device>(),
                     m_window->get());

    storage.put(m_window->get());
    storage.put(m_surface->get());

    recalculateCapabilities();
}

} // namespace engine::window
