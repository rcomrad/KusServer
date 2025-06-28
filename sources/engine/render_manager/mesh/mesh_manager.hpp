#ifndef MESH_FACTORY_HPP
#define MESH_FACTORY_HPP
#include <functional>
#include <unordered_map>

#include "engine/render_manager/vertex/vertex_usings.hpp"
#include "glm/vec2.hpp"

#include "mesh.hpp"

namespace kusengine::render
{

// const Mesh<UniversalVertex>* const

template <typename Type>
struct ChooseVertexType
{
};

class MeshManager
{
public:
    void loadMeshes();

    template <typename VertexT>
    void addMesh(const std::vector<uint32_t>& indices,
                 const std::vector<VertexT>& vertices,
                 const std::string& key);

    template <typename VertexT>
    const Mesh<VertexT>* const getMesh(std::string_view key) const;

private:
    // ----------- Universal Vertex Mesh ----------- //
    void addMeshImpl(const std::vector<uint32_t>& indices,
                     const std::vector<VertexP1UV1>& vertices,
                     const std::string& key);

    const Mesh<VertexP1UV1>* const getMeshImpl(
        std::string_view key,
        ChooseVertexType<VertexP1UV1>) const;

    std::unordered_map<std::string, Mesh<VertexP1UV1>> m_universal_mesh_storage;

    // -----------  ----------- //
};

template <typename VertexT>
const Mesh<VertexT>* const
MeshManager::getMesh(std::string_view key) const
{
    return getMeshImpl(key, ChooseVertexType<VertexT>{});
}

template <typename VertexT>
void
MeshManager::addMesh(const std::vector<uint32_t>& indices,
                     const std::vector<VertexT>& vertices,
                     const std::string& key)
{
    return addMeshImpl(indices, vertices, key);
}

}; // namespace kusengine::render

#endif // MESH_FACTORY_HPP
