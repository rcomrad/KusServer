#include "mesh_manager.hpp"

#include "engine/parsers/mesh_parser.hpp"
#include "kernel/framework/include_me.hpp"

namespace kusengine::render
{

void
MeshManager::setup(const MaterialManager& material_manager)
{
    parser::MeshParser mesh_parser;

    auto&& path = KERNEL.getFolderPath("resource") + "mesh.json";

    mesh_parser.parse(path, *this, material_manager);
}

void
MeshManager::setMeshes(
    std::unordered_map<std::string, std::unique_ptr<IMesh>>&& meshes)
{
    m_meshes = std::move(meshes);
}

const IMesh* const
MeshManager::getMesh(const std::string& name) const
{
    return m_meshes.find(name)->second.get();
}

} // namespace kusengine::render
