#ifndef TRS_MBDDI_3D_HPP
#define TRS_MBDDI_3D_HPP

#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_FORCE_RADIANS

#include "engine/render_manager/dynamics_data/mbddi_buffer/mbdd_structs.hpp"

#include "base_mbddi.hpp"

namespace kusengine::render
{
class TRS_MBDDI_3D : public BaseMBDDI<MODEL4x4_COLOR_MBDD>
{
public:
    virtual ~TRS_MBDDI_3D() = default;

    TRS_MBDDI_3D();

    void setRotation(float angle);

    void setColor(const glm::vec4& color);
    void setColor(float r, float g, float b, float a);

    void setSize(float size_x, float size_y, float size_z);
    void setSize(const glm::vec3& size);

    void setPosition(float pos_x, float pos_y, float pos_z);
    void setPosition(const glm::vec3& position);

    void updModelMatrix();

private:
    glm::mat4 translate = {1.f};
    glm::mat4 rotate    = {1.f};
    glm::mat4 scale     = {1.f};
};

}; // namespace kusengine

#endif // TRS_MBDDI_3D_HPP
