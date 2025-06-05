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
MeshFactory::createMeshImpl(const glm::vec2& size)
{

    UniversalVertex left_top_vertex(0.f, 0.f);
    left_top_vertex.setTexturePosition(0.f, 0.f);
    //
    UniversalVertex right_top_vertex(size.x, 0.f);
    right_top_vertex.setTexturePosition(1.f, 0.f);
    //
    UniversalVertex right_bottom_vertex(size.x, size.y);
    right_bottom_vertex.setTexturePosition(1.f, 1.f);
    //
    UniversalVertex left_bottom_vertex(0.f, size.y);
    left_bottom_vertex.setTexturePosition(0.f, 1.f);

    Mesh rectangle;
    rectangle.setVertices({left_top_vertex, right_top_vertex,
                           right_bottom_vertex, left_bottom_vertex});
    rectangle.setIndices({0, 1, 2, 2, 3, 0});

    return rectangle;
}

// Mesh
// MeshFactory::createUniversalMeshImpl(const glm::vec2& second,
//                                      const glm::vec2& third)
// {
//     UniversalVertex vertices[3];

//     vertices[0].setPosition(0.f, 0.f);
//     vertices[0].setTexturePosition(0.5f, 0.f);
//     //
//     vertices[1].setPosition(second.x, second.y);
//     vertices[1].setTexturePosition(1.f, 1.f);
//     //
//     vertices[2].setPosition(third.x, third.y);
//     vertices[2].setTexturePosition(0.f, 1.f);

//     Mesh triangle;
//     triangle.setVertices({vertices[0], vertices[1], vertices[2]});
//     triangle.setIndices({0, 1, 2});

//     return triangle;
// }

}; // namespace kusengine
