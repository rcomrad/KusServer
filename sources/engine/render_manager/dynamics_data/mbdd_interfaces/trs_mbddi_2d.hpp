#ifndef TRS_MBDDI_2D_HPP
#define TRS_MBDDI_2D_HPP

#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_FORCE_RADIANS

#include "engine/render_manager/dynamics_data/mbddi_buffer/mbdd_structs.hpp"

#include "base_mbddi.hpp"

namespace kusengine
{
namespace render
{
class TRS_MBDDI_2D : public BaseMBDDI<MODEL4x4_COLOR_MBDD>
{
public:
    virtual ~TRS_MBDDI_2D() = default;

    TRS_MBDDI_2D();

    void setRotation(float angle);

    void setColor(const glm::vec4& color);
    void setColor(float r, float g, float b, float a);

    void setSize(float size_x, float size_y);
    void setSize(const glm::vec2& size);

    void setPosition(float pos_x, float pos_y);
    void setPosition(const glm::vec2& position);

    void updModelMatrix();

private:
    glm::mat4 translate = {1.f};
    glm::mat4 rotate    = {1.f};
    glm::mat4 scale     = {1.f};
};
}; // namespace render
}; // namespace kusengine

#endif // TRS_MBDDI_2D_HPP
