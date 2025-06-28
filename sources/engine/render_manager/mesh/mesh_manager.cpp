#include "mesh_manager.hpp"

#include <exception>
#include <iostream>

namespace kusengine::render
{

void
MeshManager::loadMeshes()
{
    std::vector<uint32_t> inds = {0, 1, 2, 0, 2, 3};

    std::vector<VertexP1UV1> verts = {{{{0.f, 0.f}, {0.f, 0.f}}},
                                      {{{1.f, 0.f}, {1.f, 0.f}}},
                                      {{{1.f, 1.f}, {1.f, 1.f}}},
                                      {{{0.f, 1.f}, {0.f, 1.f}}}};

    addMesh<VertexP1UV1>(inds, verts, "rectangle");
}

const Mesh<VertexP1UV1>* const
MeshManager::getMeshImpl(std::string_view key,
                         ChooseVertexType<VertexP1UV1>) const
{
    auto it = m_universal_mesh_storage.find(key.data());

    if (it == m_universal_mesh_storage.end())
    {
        throw std::exception(
            (std::string(key.data()) + " does not exist in mesh manager\n")
                .data());
    }
    return &((*it).second);
}

void
MeshManager::addMeshImpl(const std::vector<uint32_t>& indices,
                         const std::vector<VertexP1UV1>& vertices,
                         const std::string& key)
{
    m_universal_mesh_storage[key] = Mesh<VertexP1UV1>(indices, vertices);
}

}; // namespace kusengine::render
