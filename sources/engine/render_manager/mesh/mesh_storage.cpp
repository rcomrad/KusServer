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

const Mesh<UniversalVertex>* const
MeshStorage::getMeshImpl(std::string_view key,
                         EmptyStruct<UniversalVertex>) const
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
                         const std::vector<UniversalVertex>& vertices,
                         const std::string& key)
{
    m_universal_mesh_storage[key] = Mesh<UniversalVertex>(indices, vertices);
}

}; // namespace render
}; // namespace kusengine
