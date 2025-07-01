#ifndef UNIVERSAL_DRAWABLE_HPP
#define UNIVERSAL_DRAWABLE_HPP

#include "engine/render_manager/drawable/basic_drawable.hpp"
#include "engine/render_manager/dynamics_data/mbdd_interfaces/trs_mbddi_2d.hpp"
#include "engine/render_manager/dynamics_data/mbdd_interfaces/trs_mbddi_3d.hpp"
#include "engine/render_manager/vertex/vertex_usings.hpp"

namespace kusengine
{
namespace render
{

using Drawable2D_P1UV1_TRS = BasicDrawable<Vertex2DP1UV1, TRS_MBDDI_2D>;

using Drawable3D_P1UV1_TRS = BasicDrawable<Vertex3DP1UV1, TRS_MBDDI_3D>;

}; // namespace render
}; // namespace kusengine

#endif // UNIVERSAL_DRAWABLE_HPP
