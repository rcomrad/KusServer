#ifndef UNIFORM_BUFFER_OBJECT_HPP
#define UNIFORM_BUFFER_OBJECT_HPP

#include <glm/glm.hpp>

namespace kusengine
{
struct UBO
{
    glm::mat4 projection;
};

bool
operator==(const UBO& left, const UBO& right);

} // namespace kusengine

#endif // UNIFORM_BUFFER_OBJECT_HPP
