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
                                          const MyVec2& size)
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

Mesh
MeshFactory::createUniversalTriangleMesh(const MyVec2& first,
                                         const MyVec2& second,
                                         const MyVec2& third)
{
    UniversalVertex vertices[3];

    vertices[0].setPosition(first.x, first.y);
    vertices[0].setTexturePosition(0.5f, 0.f);
    //
    vertices[1].setPosition(second.x, second.y);
    vertices[1].setTexturePosition(1.f, 1.f);
    //
    vertices[2].setPosition(third.x, third.y);
    vertices[2].setTexturePosition(0.f, 1.f);

    Mesh triangle;
    triangle.setVertices({vertices[0], vertices[1], vertices[2]});
    triangle.setIndices({0, 1, 2});

    return triangle;
}

}; // namespace kusengine
