#include "mesh_factory.hpp"

namespace kusengine
{

MeshFactory&
MeshFactory::getInstance()
{
    static MeshFactory fabric;
    return fabric;
}

Mesh<UniversalVertex>
MeshFactory::createUniversalRectangleMesh(const glm::vec2& position,
                                          const glm::vec2& size,
                                          const glm::vec3& color)
{

    UniversalVertex left_top_vertex({position.x, position.y}, color);
    //
    UniversalVertex right_top_vertex({position.x + size.x, position.y}, color);
    //
    UniversalVertex right_bottom_vertex({position.x + size.x,
                                        position.y + size.y}, color);
    //
    UniversalVertex left_bottom_vertex({position.x, position.y + size.y}, color);

    Mesh<UniversalVertex> rectangle;
    rectangle.setVertices({left_top_vertex, right_top_vertex,
                           right_bottom_vertex, left_bottom_vertex});
    rectangle.setIndices({0, 1, 2, 2, 3, 0});

    return rectangle;
}

}; // namespace kusengine
