#include "mesh_manager.hpp"

namespace kusengine::render
{

// TODO: builder
void
MeshManager::setup(const MaterialManager& material_manager)
{
    std::vector<VertexP2DUV> verts = {
        {{0.f, 0.f}, {0.f, 0.f}},
        {{1.f, 0.f}, {1.f, 0.f}},
        {{1.f, 1.f}, {1.f, 1.f}},
        {{0.f, 1.f}, {0.f, 1.f}}
    };

    std::vector<uint32_t> inds = {0, 1, 2, 2, 3, 0};

    {
        Mesh<VertexP2DUV> rect_mesh;
        rect_mesh.setVerts(verts);
        rect_mesh.setInds(inds);

        auto water =
            material_manager.getMaterial(Material::Type::TEXTURE, "water");
        rect_mesh.setMaterial(water);

        meshes_2d.emplace(
            std::make_pair(std::string("water_rectangle"), rect_mesh));

        //
        auto stone =
            material_manager.getMaterial(Material::Type::TEXTURE, "stone");
        rect_mesh.setMaterial(stone);

        meshes_2d.emplace(
            std::make_pair(std::string("stone_rectangle"), rect_mesh));
        //
        auto wood =
            material_manager.getMaterial(Material::Type::TEXTURE, "wood");
        rect_mesh.setMaterial(wood);

        meshes_2d.emplace(
            std::make_pair(std::string("wood_rectangle"), rect_mesh));
    }
}

template <>
const Mesh<VertexP2DUV>* const
MeshManager::getMesh<VertexP2DUV>(const std::string& mesh_name) const
{
    return &(meshes_2d.find(mesh_name)->second);
}

template <>
const Mesh<VertexP3DUV>* const
MeshManager::getMesh<VertexP3DUV>(const std::string& mesh_name) const
{
    return &(meshes_3d.find(mesh_name)->second);
}
} // namespace kusengine::render
