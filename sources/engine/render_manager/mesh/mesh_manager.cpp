#include "mesh_manager.hpp"

#include <exception>
#include <iostream>

namespace kusengine::render
{

void
MeshManager::loadMeshes()
{

    // rectangle
    std::vector<uint32_t> inds_rect = {0, 1, 2, 0, 2, 3};

    std::vector<Vertex2DP1UV1> verts_rect = {{{{0.f, 0.f}, {0.f, 0.f}}},
                                             {{{1.f, 0.f}, {1.f, 0.f}}},
                                             {{{1.f, 1.f}, {1.f, 1.f}}},
                                             {{{0.f, 1.f}, {0.f, 1.f}}}};

    addMesh<Vertex2DP1UV1>(inds_rect, verts_rect, "rectangle");

    // cube

    std::vector<uint32_t> inds_cube = {//
                                       0, 1, 2, 0, 2, 3,
                                       //
                                       4, 5, 6, 4, 6, 7,
                                       //
                                       8, 9, 10, 8, 10, 11,
                                       //
                                       12, 13, 14, 12, 14, 15,
                                       //
                                       16, 17, 18, 16, 18, 19,
                                       //
                                       20, 21, 22, 20, 22, 23};

    std::vector<Vertex3DP1UV1> verts_cube = {
        //
        {{{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f}}}, // 0
        {{{0.5f, -0.5f, 0.5f}, {1.0f, 0.0f}}},  // 1
        {{{0.5f, 0.5f, 0.5f}, {1.0f, 1.0f}}},   // 2
        {{{-0.5f, 0.5f, 0.5f}, {0.0f, 1.0f}}},  // 3

        //
        {{{0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}}},  // 4
        {{{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}}}, // 5
        {{{-0.5f, 0.5f, -0.5f}, {1.0f, 1.0f}}},  // 6
        {{{0.5f, 0.5f, -0.5f}, {0.0f, 1.0f}}},   // 7

        //
        {{{-0.5f, 0.5f, 0.5f}, {0.0f, 0.0f}}},  // 8
        {{{0.5f, 0.5f, 0.5f}, {1.0f, 0.0f}}},   // 9
        {{{0.5f, 0.5f, -0.5f}, {1.0f, 1.0f}}},  // 10
        {{{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f}}}, // 11

        //
        {{{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}}}, // 12
        {{{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}}},  // 13
        {{{0.5f, -0.5f, 0.5f}, {1.0f, 1.0f}}},   // 14
        {{{-0.5f, -0.5f, 0.5f}, {0.0f, 1.0f}}},  // 15

        //
        {{{0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}}}, // 16
        {{{0.5f, -0.5f, 0.5f}, {1.0f, 0.0f}}},  // 17
        {{{0.5f, 0.5f, 0.5f}, {1.0f, 1.0f}}},   // 18
        {{{0.5f, 0.5f, -0.5f}, {0.0f, 1.0f}}},  // 19

        //
        {{{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f}}},  // 20
        {{{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}}}, // 21
        {{{-0.5f, 0.5f, -0.5f}, {1.0f, 1.0f}}},  // 22
        {{{-0.5f, 0.5f, 0.5f}, {0.0f, 1.0f}}}    // 23
    };

    addMesh<Vertex3DP1UV1>(inds_cube, verts_cube, "cube");
}

const Mesh<Vertex2DP1UV1>* const
MeshManager::getMeshImpl(std::string_view key,
                         ChooseVertexType<Vertex2DP1UV1>) const
{
    auto it = m_2d_p1_uv1_mesh_storage.find(key.data());

    if (it == m_2d_p1_uv1_mesh_storage.end())
    {
        throw std::exception(
            (std::string(key.data()) + " does not exist in mesh manager\n")
                .data());
    }
    return &((*it).second);
}

void
MeshManager::addMeshImpl(const std::vector<uint32_t>& indices,
                         const std::vector<Vertex2DP1UV1>& vertices,
                         const std::string& key)
{
    m_2d_p1_uv1_mesh_storage[key] = Mesh<Vertex2DP1UV1>(indices, vertices);
}

// ----------- 3d Vertex Mesh ----------- //
void
MeshManager::addMeshImpl(const std::vector<uint32_t>& indices,
                         const std::vector<Vertex3DP1UV1>& vertices,
                         const std::string& key)
{
    m_3d_p1_uv1_mesh_storage[key] = Mesh<Vertex3DP1UV1>(indices, vertices);
}

const Mesh<Vertex3DP1UV1>* const
MeshManager::getMeshImpl(std::string_view key,
                         ChooseVertexType<Vertex3DP1UV1>) const
{
    auto it = m_3d_p1_uv1_mesh_storage.find(key.data());

    if (it == m_3d_p1_uv1_mesh_storage.end())
    {
        throw std::exception(
            (std::string(key.data()) + " does not exist in mesh manager\n")
                .data());
    }
    return &((*it).second);
}
}; // namespace kusengine::render
