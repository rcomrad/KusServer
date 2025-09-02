#include "mesh_parser.hpp"

#include <nlohmann/json.hpp>

#include <fstream>

#include "parser_basic_functions.hpp"
namespace kusengine::parser
{

struct MeshParseData
{
    std::string name;
    std::string vertex_type;
    std::string material;
    std::vector<uint32_t> indices;
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

void
to_json(nlohmann::json& j, const MeshParseData& mesh)
{
    j = nlohmann::json{
        {"name",        mesh.name       },
        {"material",    mesh.material   },
        {"vertex_type", mesh.vertex_type},
        {"indices",     mesh.indices    }
    };
}

void
from_json(const nlohmann::json& j, MeshParseData& mesh)
{
    j.at("name").get_to(mesh.name);
    j.at("material").get_to(mesh.material);
    j.at("vertex_type").get_to(mesh.vertex_type);
    j.at("indices").get_to(mesh.indices);
}

template <>
void
MeshParser::parseVerts<"P2DUV">()
{
}

std::unordered_map<std::string, std::unique_ptr<render::IMesh>>
MeshParser::parse(const std::string& filename,
                  render::MeshManager& mesh_manager)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    nlohmann::json j;
    file >> j;

    std::vector<MeshParseData> meshes_data =
        j["meshes"].get<std::vector<MeshParseData>>();

    for (auto&& mesh_data : meshes_data)
    {
    }
}
} // namespace kusengine::parser
