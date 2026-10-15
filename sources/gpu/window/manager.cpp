#include "manager.hpp"

#include "kernel/framework/include_me.hpp"

#include "gpu/hardware/device.hpp"
#include "gpu/hardware/instance.hpp"
#include "gpu/utils/variable.hpp"

gpu::window::Manager::Manager(hard::Instance& a_instance,
                              hard::Device& a_device)
    : m_device(a_device),
      m_surface(a_instance, m_device, m_window),
      m_characteristics(m_device, m_surface)
{
    LOG_INFO("window created");
}

void
gpu::window::Manager::recalculateCapabilities()
{
    m_window.updateSize();
    m_characteristics = SurfaceCharacteristics(m_device, m_surface);
}

void
gpu::window::Manager::poolEvents(EventCarrier& a_event_carrier)
{
    m_window.poolEvents(a_event_carrier);
}

gpu::window::Surface&
gpu::window::Manager::getSurface()
{
    return m_surface;
}

gpu::window::SurfaceCharacteristics&
gpu::window::Manager::getCharacteristics()
{
    return m_characteristics;
}
