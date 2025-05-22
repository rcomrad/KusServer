#include "mesh_factory.hpp"

namespace kusengine
{

MeshFactory&
MeshFactory::getInstance()
{
    static MeshFactory fabric;
    return fabric;
}

Mesh
MeshFactory::createUniversalRectangleMesh(const MyVec2& position,
                                          const MyVec2& size,
                                          const MyVec3& color)
{

    UniversalVertex left_top_vertex(position.x, position.y);
    left_top_vertex.setTexturePosition(0, 0);
    //
    UniversalVertex right_top_vertex(position.x + size.x, position.y);
    right_top_vertex.setTexturePosition(1, 0);
    //
    UniversalVertex right_bottom_vertex(position.x + size.x,
                                        position.y + size.y);
    right_bottom_vertex.setTexturePosition(1, 1);
    //
    UniversalVertex left_bottom_vertex(position.x, position.y + size.y);
    left_bottom_vertex.setTexturePosition(0, 1);

    Mesh rectangle;
    rectangle.setVertices({left_top_vertex, right_top_vertex,
                           right_bottom_vertex, left_bottom_vertex});
    rectangle.setIndices({0, 1, 2, 2, 3, 0});

    return rectangle;
}

}; // namespace kusengine
