#include "rectangle_shape.hpp"

#include "engine/graphics/models/model/mesh/mesh_factory.hpp"
namespace kusengine
{

RectangleShape::RectangleShape() : Shape(getMesh())
{
}

std::shared_ptr<Mesh>
RectangleShape::getMesh()
{
    std::vector<glm::vec2> vertices = {
        {0.f, 0.f},
        {1.f, 0.f},
        {1.f, 1.f},
        {0.f, 1.f}
    };
    std::vector<glm::vec2> texture_vertices = {
        {0.f, 0.f},
        {1.f, 0.f},
        {1.f, 1.f},
        {0.f, 1.f}
    };

    std::vector<uint32_t> indices = {0, 1, 2, 2, 3, 0};

    return MESH_FACTORY.getMesh(vertices, texture_vertices, indices);
}

std::unique_ptr<Shape>
RectangleShape::makeUniquePtrCopy() const
{
    return std::make_unique<RectangleShape>(*this);
}

}; // namespace kusengine
