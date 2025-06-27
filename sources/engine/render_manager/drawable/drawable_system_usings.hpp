#ifndef DRAWABLE_SYSTEM_USINGS_HPP
#define DRAWABLE_SYSTEM_USINGS_HPP

#include "engine/render_manager/drawable/drawable_system.hpp"
#include "engine/render_manager/drawable/drawable_usings.hpp"
#include "engine/render_manager/dynamics_data/mbddi_buffer/mbdd_structs.hpp"
#include "engine/render_manager/dynamics_data/uniform_buffer_object.hpp"

namespace kusengine
{
namespace render
{
using DrawableSystem_P1UV1_TRS =
    DrawableSystem<Drawable_P1UV1_TRS,
                   Drawable_P1UV1_TRS::MBDDInterfaceType::MBDDtype>;
};
}; // namespace kusengine

#endif // DRAWABLE_SYSTEM_USINGS_HPP
