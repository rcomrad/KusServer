#ifndef JSON_PARSER_HPP
#define JSON_PARSER_HPP

#include <nlohmann/json.hpp>

#include <optional>

#include "engine/render_manager/vertex/vertex_usings.hpp"

namespace kusengine::json_parser
{

// models //

struct ModelData
{
    std::string name;
    std::string mesh;
    std::string texture;
};

std::vector<ModelData>
parseModels2D();

// meshes //

struct MeshData
{
    std::string name;
    std::vector<uint32_t> inds;
    std::vector<render::Vertex2DP1UV1> verts;
};

std::vector<MeshData>
parseMeshes2D();

// -- //

// textures //

struct TextureData
{
    std::string name;
    std::string filename;
    std::vector<glm::vec2> uv_coords;
};

std::vector<TextureData>
parseTextures();

} // namespace kusengine::json_parser

#endif // JSON_PARSER_HPP
