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
    glm::vec4 color;
    glm::mat4 rotation;
    glm::mat4 scale;
    glm::mat4 translation;
};

class ModelBasicDynamicsDataInterface
{
public:
    ModelBasicDynamicsDataInterface() = default;

    void linkData(MBDD* data);

    void setRotation(float angle);

    void setColor(const glm::vec4& color, bool is_0_1_range = true);
    void setColor(float r, float g, float b, float a, bool is_0_1_range = true);

    void setScale(float scale_x, float scale_y, bool is_0_1_range = true);
    void setScale(const glm::vec2& scale, bool is_0_1_range = true);

    void setPosition(float pos_x, float pos_y, bool is_0_1_range = true);
    void setPosition(const glm::vec2& position, bool is_0_1_range = true);

    void setWindowSize(float x, float y);

private:
    static glm::vec2 m_window_size;

    MBDD* m_data;
};

}; // namespace kusengine

#endif // MODEL_BASIC_DYNAMICS_DATA_HPP
