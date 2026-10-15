#pragma once

#include "surface.hpp"
#include "surface_characteristics.hpp"
#include "window.hpp"

namespace gpu
{

namespace hard
{
class Device;
class Instance;
} // namespace hard

namespace window
{

class Manager
{
public:
    Manager(hard::Instance& a_instance, hard::Device& a_device);

    void recalculateCapabilities();
    void poolEvents(EventCarrier& a_event_carrier);

    Surface& getSurface();
    SurfaceCharacteristics& getCharacteristics();

private:
    hard::Device& m_device;

    Window m_window;
    Surface m_surface;
    SurfaceCharacteristics m_characteristics;
};

} // namespace window

} // namespace gpu
