#ifndef MODEL_BASIC_DYNAMICS_DATA_HPP
#define MODEL_BASIC_DYNAMICS_DATA_HPP

#include <vector>

#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_FORCE_RADIANS

#include "glm/mat3x3.hpp"
#include "glm/vec3.hpp"

// ------------ MODEL POSITION ----------- //
/////////////////////////////////////////////////////
// 0 -1                                       1 -1 //
//                                                 //
//                                                 //
//                                                 //
//                      0, 0                       //
//                                                 //
//                                                 //
//                                                 //
// 1 -1                                        1 1 //
/////////////////////////////////////////////////////

namespace kusengine
{

struct MBDD // use 4, not 3, because shader alligning
{
    MBDD();
    glm::vec4 color;
    glm::mat4 model;
};

class ModelBasicDynamicsDataInterface
{
public:
    ModelBasicDynamicsDataInterface();

    ~ModelBasicDynamicsDataInterface();

    ModelBasicDynamicsDataInterface(
        const ModelBasicDynamicsDataInterface& other);
    ModelBasicDynamicsDataInterface(ModelBasicDynamicsDataInterface&& other);

    ModelBasicDynamicsDataInterface& operator=(
        const ModelBasicDynamicsDataInterface& other);
    ModelBasicDynamicsDataInterface& operator=(
        ModelBasicDynamicsDataInterface&& other);

    void linkData(MBDD* data);

    void setRotation(float angle);

    void setColor(const glm::vec4& color);
    void setColor(float r, float g, float b, float a);

    void setSize(float size_x, float size_y);
    void setSize(const glm::vec2& size);

    void setPosition(float pos_x, float pos_y);
    void setPosition(const glm::vec2& position);

    void upd();

private:
    glm::mat4 translate;
    glm::mat4 rotate;
    glm::mat4 scale;

    bool is_linked;

    MBDD* m_data;
};

}; // namespace kusengine

#endif // MODEL_BASIC_DYNAMICS_DATA_HPP
