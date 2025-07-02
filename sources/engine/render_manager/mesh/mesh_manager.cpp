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
                                       0, 1, 2, 2, 3, 0,
                                       //
                                       4, 6, 5, 4, 7, 6,
                                       //
                                       8, 10, 9, 8, 11, 10,
                                       //
                                       12, 13, 14, 12, 14, 15,
                                       //
                                       16, 17, 18, 16, 18, 19,
                                       //
                                       20, 22, 21, 20, 23, 22};

    std::vector<glm::vec2> uv_arr = {
        {0.f,             0.f}, //  0
        {1.f / 3.f,       0.f}, //  1
        {1.f / 3.f * 2.f, 0.f}, //  2
        {1.f,             0.f}, //  3
        {0.f,             1.f}, //  4
        {1.f / 3.f,       1.f}, //  5
        {1.f / 3.f * 2.f, 1.f}, //  6
        {1.f,             1.f}  //  7
    };

    std::vector<Vertex3DP1UV1> verts_cube = {//
                                             {{{0.0f, 0.0f, 1.0f}, uv_arr[0]}},
                                             {{{1.0f, 0.0f, 1.0f}, uv_arr[1]}},
                                             {{{1.0f, 1.0f, 1.0f}, uv_arr[5]}},
                                             {{{0.0f, 1.0f, 1.0f}, uv_arr[4]}},

                                             //
                                             {{{0.0f, 0.0f, 0.0f}, uv_arr[1]}},
                                             {{{1.0f, 0.0f, 0.0f}, uv_arr[2]}},
                                             {{{1.0f, 1.0f, 0.0f}, uv_arr[6]}},
                                             {{{0.0f, 1.0f, 0.0f}, uv_arr[5]}},

                                             //
                                             {{{0.0f, 1.0f, 0.0f}, uv_arr[2]}},
                                             {{{1.0f, 1.0f, 0.0f}, uv_arr[3]}},
                                             {{{1.0f, 1.0f, 1.0f}, uv_arr[7]}},
                                             {{{0.0f, 1.0f, 1.0f}, uv_arr[6]}},

                                             //
                                             {{{0.0f, 0.0f, 0.0f}, uv_arr[0]}},
                                             {{{1.0f, 0.0f, 0.0f}, uv_arr[1]}},
                                             {{{1.0f, 0.0f, 1.0f}, uv_arr[5]}},
                                             {{{0.0f, 0.0f, 1.0f}, uv_arr[4]}},

                                             //
                                             {{{1.0f, 0.0f, 0.0f}, uv_arr[1]}},
                                             {{{1.0f, 1.0f, 0.0f}, uv_arr[2]}},
                                             {{{1.0f, 1.0f, 1.0f}, uv_arr[6]}},
                                             {{{1.0f, 0.0f, 1.0f}, uv_arr[5]}},

                                             //
                                             {{{0.0f, 0.0f, 0.0f}, uv_arr[2]}},
                                             {{{0.0f, 1.0f, 0.0f}, uv_arr[3]}},
                                             {{{0.0f, 1.0f, 1.0f}, uv_arr[7]}},
                                             {{{0.0f, 0.0f, 1.0f}, uv_arr[6]}}

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
