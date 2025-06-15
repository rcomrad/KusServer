#include "mesh_factory.hpp"

#include <iostream>

namespace kusengine
{

MeshFactory&
MeshFactory::getInstance()
{
    static MeshFactory fabric;
    return fabric;
}

std::shared_ptr<Mesh>
MeshFactory::getMesh(const std::vector<glm::vec2>& position_verts,
                     const std::vector<glm::vec2>& texture_verts,
                     const std::vector<uint32_t>& indices)
{
    Mesh mesh = createMesh(position_verts, texture_verts, indices);

    std::shared_ptr<Mesh> result;

    auto it = std::find_if(created_meshes.begin(), created_meshes.end(),
                           [&mesh](const std::shared_ptr<Mesh>& other)
                           { return *other == mesh; });

    if (it == created_meshes.end())
    {
        result = std::make_shared<Mesh>(mesh);
        created_meshes.emplace_back(result);
    }
    else
    {
        result = *it;
    }

    return result;
}

Mesh
MeshFactory::createMesh(const std::vector<glm::vec2>& position_verts,
                        const std::vector<glm::vec2>& texture_verts,
                        const std::vector<uint32_t>& indices)
{
    if (position_verts.size() != texture_verts.size())
    {
        std::cout << "MeshFactory cant create mesh. PosVert and TextVerts have "
                     "different sizes\n";
        return Mesh{};
    }
    std::vector<kusengine::UniversalVertex> mesh_arg(position_verts.size());

    for (int i = 0; i < position_verts.size(); ++i)
    {
        mesh_arg[i].setPosition(position_verts[i].x, position_verts[i].y);
        mesh_arg[i].setTexturePosition(texture_verts[i].x, texture_verts[i].y);
    }
    Mesh res;
    res.setVertices(mesh_arg);
    res.setIndices(indices);
    return res;
}

// Mesh
// MeshFactory::createMeshImpl(const std::vector<glm::vec2>& vec2_vec)
// {
//     Mesh mesh;
//     mesh.setVertices(vec2_vec);
// }
// Mesh
// MeshFactory::createMeshImpl(const glm::vec2& size)
// {

//     UniversalVertex left_top_vertex(0.f, 0.f);
//     left_top_vertex.setTexturePosition(0.f, 0.f);
//     //
//     UniversalVertex right_top_vertex(size.x, 0.f);
//     right_top_vertex.setTexturePosition(1.f, 0.f);
//     //
//     UniversalVertex right_bottom_vertex(size.x, size.y);
//     right_bottom_vertex.setTexturePosition(1.f, 1.f);
//     //
//     UniversalVertex left_bottom_vertex(0.f, size.y);
//     left_bottom_vertex.setTexturePosition(0.f, 1.f);

//     Mesh rectangle;
//     rectangle.setVertices({left_top_vertex, right_top_vertex,
//                            right_bottom_vertex, left_bottom_vertex});
//     rectangle.setIndices({0, 1, 2, 2, 3, 0});

//     return rectangle;
// }

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
