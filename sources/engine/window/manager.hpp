#pragma once

#include <vector>

#include "kernel/framework/variable/include_me.hpp"
#include "kernel/utility/type/declaration/lifecycle_manager.hpp"
#include "kernel/utility/type/declaration/multitype_storage.hpp"

#include "surface.hpp"
#include "surface_characteristics.hpp"
#include "window.hpp"

namespace engine::window
{

class Manager
{
public:
    Manager(std::shared_ptr<core::MultitypeStorage> a_obj_ref_storage);

    void initialize();

    inline bool isClosed()
    {
        return m_window->isClosed();
    }

private:
    core::IntVar m_width;
    core::IntVar m_height;
    std::shared_ptr<core::MultitypeStorage> m_obj_ref_storage;

    utils::LifecycleManager<Window> m_window;
    utils::LifecycleManager<Surface> m_surface;
    utils::LifecycleManager<SurfaceCharacteristics> m_characteristics;
};

} // namespace engine::window
