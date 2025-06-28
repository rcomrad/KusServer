#ifndef MBDD_STRUCTS_HPP
#define MBDD_STRUCTS_HPP

#include "glm/mat3x3.hpp"
#include "glm/vec3.hpp"

namespace kusengine
{
namespace render
{
struct MODEL4x4_COLOR_MBDD // use 4, not 3, because shader alligning
{
    glm::vec4 color = {1.f, 1.f, 1.f, 1.f};
    glm::mat4 model = {1};
};
}; // namespace render
}; // namespace kusengine

#endif // MBDD_STRUCTS_HPP
