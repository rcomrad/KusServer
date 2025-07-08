#ifndef DRAWABLE_3D_P1UV1_TRS_HPP
#define DRAWABLE_3D_P1UV1_TRS_HPP

#include "engine/render_manager/drawable/basic_drawable.hpp"
#include "engine/render_manager/dynamics_data/mbdd_interfaces/trs_mbddi_3d.hpp"
#include "engine/render_manager/vertex/vertex_usings.hpp"

namespace kusengine::render
{

class Drawable3D_P1UV1_TRS : public BasicDrawable<Vertex3DP1UV1, TRS_MBDDI_3D>
{
public:
};

}; // namespace kusengine::render

#endif // DRAWABLE_3D_P1UV1_TRS_HPP
