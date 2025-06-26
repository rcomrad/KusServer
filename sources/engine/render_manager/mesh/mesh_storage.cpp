#include "mesh_storage.hpp"

#include <exception>
#include <iostream>

namespace kusengine
{
namespace render
{

MeshStorage::MeshStorage()
{
}

const Mesh<VertexP1UV1>* const
MeshStorage::getMeshImpl(std::string_view key, EmptyStruct<VertexP1UV1>) const
{
    auto it = m_universal_mesh_storage.find(key.data());

    if (it == m_universal_mesh_storage.end())
    {
        throw std::exception(
            (std::string(key.data()) + " does not exist in mesh storage\n")
                .data());
    }
    return &((*it).second);
}

void
MeshStorage::addMeshImpl(const std::vector<uint32_t>& indices,
                         const std::vector<VertexP1UV1>& vertices,
                         const std::string& key)
{
    m_universal_mesh_storage[key] = Mesh<VertexP1UV1>(indices, vertices);
}

}; // namespace render
}; // namespace kusengine
