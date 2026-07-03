#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

namespace gpu::sprite
{

struct SpritePushData
{
    glm::vec2 scaler;
    glm::vec2 offset;
    // alignas(16) glm::vec3 color;
};

} // namespace gpu::sprite
