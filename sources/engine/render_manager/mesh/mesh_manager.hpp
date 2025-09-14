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

    // void setMeshes(
    // std::unordered_map<std::string, std::unique_ptr<IMesh>>&& meshes);

    template <typename Mesh_t>
    void pushMesh(const std::string& name, const Mesh_t& mesh)
    {
        m_meshes.emplace(name, std::make_unique<Mesh_t>(mesh));
    };

    const IMesh* const getMesh(const std::string& name) const;

private:
    std::unordered_map<std::string, std::unique_ptr<IMesh>> m_meshes;
};

} // namespace kusengine::render

#endif // MESH_MANAGER_HPP
