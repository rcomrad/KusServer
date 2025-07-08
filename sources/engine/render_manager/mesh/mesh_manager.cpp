#include "mesh_manager.hpp"

#include <exception>
#include <iostream>

#include "engine/json_parser/model_2d_parser.hpp"

namespace kusengine::render
{

void
MeshManager::loadMeshes()
{
    // 2d

    auto meshes_data = json_parser::parseMeshes2D();

    for (auto& md : meshes_data)
    {
        addMesh<Vertex2DP1UV1>(md.inds, md.verts, md.name);
    }
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
