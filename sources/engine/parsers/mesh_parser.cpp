#include "mesh_parser.hpp"

#include <nlohmann/json.hpp>

#include <fstream>

#include "verts_attributes_parsers_funcs.hpp"
namespace kusengine::parser
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

template <typename Vert_t>
struct MeshParseData
{
    std::string name;
    std::string material;
    std::vector<uint32_t> indices;
    std::vector<Vert_t> vertices;
};

void
to_json(nlohmann::json& j, const std::vector<uint32_t>& indices)
{
    j = nlohmann::json::array();
    j.get_ref<nlohmann::json::array_t&>().reserve(indices.size());

    for (const auto& index : indices)
    {
        j.push_back(index);
    }
}

void
from_json(const nlohmann::json& j, std::vector<uint32_t>& indices)
{
    indices.clear();

    for (const auto& element : j)
    {
        indices.push_back(element.get<uint32_t>());
    }
}

template <typename Vert_t>
void
to_json(nlohmann::json& j, const MeshParseData<Vert_t>& mesh)
{
    j = nlohmann::json{
        {"name",     mesh.name    },
        {"material", mesh.material},
        {"indices",  mesh.indices },
        {"vertices", mesh.vertices}
    };
}

template <typename Vert_t>
void
from_json(const nlohmann::json& j, MeshParseData<Vert_t>& mesh)
{
    j.at("name").get_to(mesh.name);
    j.at("material").get_to(mesh.material);
    j.at("indices").get_to(mesh.indices);
    j.at("vertices").get_to(mesh.vertices);
}

void
MeshParser::parse(const std::string& filename,
                  render::MeshManager& mesh_manager,
                  const render::MaterialManager& material_manager)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    nlohmann::json j;
    file >> j;

    std::vector<MeshParseData<render::VertexP2DUV>> meshes_data =
        j["P2DUV"].get<std::vector<MeshParseData<render::VertexP2DUV>>>();

    std::unordered_map<std::string, std::unique_ptr<render::IMesh>> meshes;

    // mesh rect
    std::vector<render::VertexP2DUV> verts = {
        {{0.f, 0.f}, {0.f, 0.f}},
        {{1.f, 0.f}, {1.f, 0.f}},
        {{1.f, 1.f}, {1.f, 1.f}},
        {{0.f, 1.f}, {0.f, 1.f}}
    };
    std::vector<uint32_t> inds = {0, 1, 2, 2, 3, 0};

    render::Mesh<render::VertexP2DUV> rect_mesh;
    rect_mesh.setVertices(translateToCharVector(verts));
    rect_mesh.setInds(inds);

    auto water = material_manager.getMaterial("stat_water");
    rect_mesh.setMaterial(water);
    ////////////

    for (auto&& mesh_data : meshes_data)
    {
        render::Mesh<render::VertexP2DUV> mesh;
        mesh.setInds(mesh_data.indices);
        mesh.setVertices(translateToCharVector(mesh_data.vertices));
        mesh.setMaterial(material_manager.getMaterial(mesh_data.material));

        mesh_manager.pushMesh(mesh_data.name, mesh);
    }

    // mesh_manager.setMeshes(std::move(meshes));
}
} // namespace kusengine::parser
