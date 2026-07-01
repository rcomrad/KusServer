#pragma once

#include "kernel/framework/variable/include_me.hpp"
#include "kernel/utility/type/declaration/lifecycle_manager.hpp"
#include "kernel/utility/type/declaration/multitype_storage.hpp"

#include <vector>

#include "gpu/hardware/instance.hpp"

#include "surface.hpp"
#include "surface_characteristics.hpp"
#include "window.hpp"

namespace gpu::window
{

class Manager
{
public:
    Manager(std::shared_ptr<core::MultitypeStorage> a_obj_ref_storage);

    void initialize();
    void recalculateCapabilities();

    void poolEvents(EventCarrier& a_event_carrier);

private:
    std::shared_ptr<core::MultitypeStorage> m_obj_ref_storage;

    utils::LifecycleManager<Window> m_window;
    utils::LifecycleManager<Surface> m_surface;
    utils::LifecycleManager<SurfaceCharacteristics> m_characteristics;
};

} // namespace gpu::window
