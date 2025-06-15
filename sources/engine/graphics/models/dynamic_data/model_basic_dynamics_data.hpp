#ifndef MODEL_BASIC_DYNAMICS_DATA_HPP
#define MODEL_BASIC_DYNAMICS_DATA_HPP

#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_FORCE_RADIANS

#include "mbddi_buffer.hpp"

namespace kusengine
{

class ModelBasicDynamicsDataInterface : public MBDDIBuffer
{
public:
    virtual ~ModelBasicDynamicsDataInterface() = default;

    ModelBasicDynamicsDataInterface();

    void setRotation(float angle);

    void setColor(const glm::vec4& color);
    void setColor(float r, float g, float b, float a);

    void setSize(float size_x, float size_y);
    void setSize(const glm::vec2& size);

    void setPosition(float pos_x, float pos_y);
    void setPosition(const glm::vec2& position);

    void updModelMatrix();

private:
    glm::mat4 translate;
    glm::mat4 rotate;
    glm::mat4 scale;
};

}; // namespace kusengine

#endif // MODEL_BASIC_DYNAMICS_DATA_HPP
