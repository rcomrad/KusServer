#ifndef DRAWABLE_2D_P1UV1_TRS_HPP
#define DRAWABLE_2D_P1UV1_TRS_HPP

#include "engine/render_manager/drawable/basic_drawable.hpp"
#include "engine/render_manager/dynamics_data/mbdd_interfaces/trs_mbddi_2d.hpp"
#include "engine/render_manager/vertex/vertex_usings.hpp"

namespace kusengine::render
{

class Drawable2D_P1UV1_TRS : public BasicDrawable<Vertex2DP1UV1, TRS_MBDDI_2D>
{
public:
    // void loadModel(const std::string& model_name) override;
};

}; // namespace kusengine::render

#endif // DRAWABLE_2D_P1UV1_TRS_HPP
