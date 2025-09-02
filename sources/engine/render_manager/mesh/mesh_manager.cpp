#include "mesh_manager.hpp"

namespace kusengine::render
{

template <typename Vert_t>
std::vector<char>
translateToCharVector(const std::vector<Vert_t>& verts)
{
    std::vector<char> res;
    res.reserve(verts.size() * Vert_t{}.byteSize());

    for (int i = 0; i < verts.size(); ++i)
    {
        verts[i].pushTo(res);
    }

    return res;
}

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
        // mesh rect
        Mesh<VertexP2DUV> rect_mesh;

        rect_mesh.setVertices(translateToCharVector(verts));
        rect_mesh.setInds(inds);

        ////////////

        {
            auto mesh = rect_mesh;

            auto water = material_manager.getMaterial(
                Material::Type::TEXTURE_ZONE, "stat_water");
            mesh.setMaterial(water);

            m_meshes.emplace(
                std::make_pair(std::string("water_rectangle"),
                               std::make_unique<Mesh<VertexP2DUV>>(mesh)));
        }

        //
        {
            auto mesh = rect_mesh;

            auto stone = material_manager.getMaterial(
                Material::Type::TEXTURE_ZONE, "stat_stone");
            mesh.setMaterial(stone);

            m_meshes.emplace(
                std::make_pair(std::string("stone_rectangle"),
                               std::make_unique<Mesh<VertexP2DUV>>(mesh)));
        }
        //
        {
            auto mesh = rect_mesh;

            auto wood = material_manager.getMaterial(
                Material::Type::TEXTURE_ZONE, "stat_wood");
            mesh.setMaterial(wood);

            m_meshes.emplace(
                std::make_pair(std::string("wood_rectangle"),
                               std::make_unique<Mesh<VertexP2DUV>>(mesh)));
        }
    }
}

const IMesh* const
MeshManager::getMesh(const std::string& name) const
{
    return m_meshes.find(name)->second.get();
}

} // namespace kusengine::render
