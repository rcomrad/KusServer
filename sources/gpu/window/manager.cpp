#include "manager.hpp"

#include "kernel/framework/include_me.hpp"

#include "gpu/hardware/device.hpp"
#include "gpu/hardware/instance.hpp"
#include "gpu/utils/variable.hpp"

gpu::window::Manager::Manager(hard::Instance& a_instance,
                              hard::Device& a_device)
    : m_surface(a_instance, a_device, m_window),
      m_characteristics(a_device, m_surface)
{
    LOG_INFO("window created");
}

void
gpu::window::Manager::poolEvents(EventCarrier& a_event_carrier)
{
    m_window->poolEvents(a_event_carrier);
}

gpu::window::Surface&
gpu::window::Manager::getSurface()
{
    m_surface;
}

const gpu::window::SurfaceCharacteristics&
gpu::window::Manager::getCharacteristics() const
{
    m_characteristics;
}
