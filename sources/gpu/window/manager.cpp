#include "manager.hpp"

#include "kernel/framework/include_me.hpp"

#include "gpu/utils/variable.hpp"

gpu::window::Manager::Manager(
    std::shared_ptr<core::MultitypeStorage> a_obj_ref_storage)
    : m_obj_ref_storage(a_obj_ref_storage)
{
}

void
gpu::window::Manager::initialize()
{
    SCOPED_TRACE_INIT("window manager");

    auto& storage = *m_obj_ref_storage;

    m_window.create();
    m_surface.create(storage.get<hard::Instance>(), storage.get<hard::Device>(),
                     m_window->get());

    storage.put(m_window->get());
    storage.put(*m_surface);

    recalculateCapabilities();
}

void
gpu::window::Manager::recalculateCapabilities()
{
    m_window->updateSize();

    auto& storage = *m_obj_ref_storage;
    m_characteristics.create(storage.get<hard::Device>(), *m_surface);

    storage.reset(m_characteristics->family_index);
    storage.reset(m_characteristics->format);
    storage.reset(m_characteristics->color_space);
    storage.reset(m_characteristics->present_mode);
    storage.reset(m_characteristics
                      ->capability); // TODO: possably need to reset only this
    storage.reset(m_characteristics->image_num);
}

void
gpu::window::Manager::poolEvents(EventCarrier& a_event_carrier)
{
    m_window->poolEvents(a_event_carrier);
}
