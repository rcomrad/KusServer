#include "rectangle_shape.hpp"

#include "engine/render_objects/model/mesh/mesh_factory.hpp"
namespace kusengine
{

RectangleShape::RectangleShape()
    : Shape(MESH_FACTORY.createMesh(glm::vec2{1.f, 1.f}))
{
}
}; // namespace kusengine
