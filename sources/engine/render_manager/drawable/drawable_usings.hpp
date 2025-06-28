#ifndef UNIVERSAL_DRAWABLE_HPP
#define UNIVERSAL_DRAWABLE_HPP

#include "engine/render_manager/drawable/basic_drawable.hpp"
#include "engine/render_manager/dynamics_data/mbdd_interfaces/trs_mbddi.hpp"
#include "engine/render_manager/vertex/vertex_usings.hpp"

namespace kusengine
{
namespace render
{

using Drawable_P1UV1_TRS = BasicDrawable<VertexP1UV1, TRS_MBDDI>;

}; // namespace render
}; // namespace kusengine

#endif // UNIVERSAL_DRAWABLE_HPP
