#include "shape.hpp"

namespace kusengine
{
void
Shape::setTexture(std::string_view texture_name)
{
    m_texture_name = texture_name;
}
}; // namespace kusengine
