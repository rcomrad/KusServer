#ifndef MESH_MANAGER_HPP
#define MESH_MANAGER_HPP

#include <unordered_map>

#include "engine/render_manager/material/material_manager.hpp"
#include "engine/render_manager/vertex/vertex_p2d_uv.hpp"
#include "engine/render_manager/vertex/vertex_p3d_uv.hpp"

#include "mesh.hpp"

namespace kusengine::render
{

class MeshManager
{
public:
    void setup(const MaterialManager& material_manager);

    template <typename Vertex_t>
    const Mesh<Vertex_t>* const getMesh(const std::string& form_name) const;

private:
    std::unordered_map<std::string, Mesh<VertexP2DUV>> meshes_2d;

    std::unordered_map<std::string, Mesh<VertexP3DUV>> meshes_3d;
};

extern template const Mesh<VertexP2DUV>* const
MeshManager::getMesh<VertexP2DUV>(const std::string& mesh_name) const;

extern template const Mesh<VertexP3DUV>* const
MeshManager::getMesh<VertexP3DUV>(const std::string& mesh_name) const;

} // namespace kusengine::render

#endif // MESH_MANAGER_HPP
