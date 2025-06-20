#ifndef MESH_FACTORY_HPP
#define MESH_FACTORY_HPP
#include <functional>
#include <unordered_map>

#include "glm/vec2.hpp"

#include "mesh.hpp"

namespace kusengine
{
namespace render
{

// const Mesh<UniversalVertex>* const

template <typename Type>
struct EmptyStruct
{
};

class MeshStorage
{
public:
    MeshStorage();

    template <typename VertexType>
    void addMesh(const std::vector<uint32_t>& indices,
                 const std::vector<VertexType>& vertices,
                 const std::string& key);

    template <typename VertexType>
    const Mesh<VertexType>* const getMesh(std::string_view key) const;

private:
    // ----------- Universal Vertex Mesh ----------- //
    void addMeshImpl(const std::vector<uint32_t>& indices,
                     const std::vector<UniversalVertex>& vertices,
                     const std::string& key);

    const Mesh<UniversalVertex>* const getMeshImpl(
        std::string_view key,
        EmptyStruct<UniversalVertex>) const;

    std::unordered_map<std::string, Mesh<UniversalVertex>>
        m_universal_mesh_storage;

    // -----------  ----------- //
};

template <typename VertexType>
const Mesh<VertexType>* const
MeshStorage::getMesh(std::string_view key) const
{
    return getMeshImpl(key, EmptyStruct<VertexType>{});
}

template <typename VertexType>
void
MeshStorage::addMesh(const std::vector<uint32_t>& indices,
                     const std::vector<VertexType>& vertices,
                     const std::string& key)
{
    return addMeshImpl(indices, vertices, key);
}

}; // namespace render
}; // namespace kusengine

#endif // MESH_FACTORY_HPP
