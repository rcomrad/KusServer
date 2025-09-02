#ifndef JSON_PARSER_HPP
#define JSON_PARSER_HPP

#include <nlohmann/json.hpp>

#include <optional>

// #include "engine/render_manager/vertex/vertex_usings.hpp"

namespace kusengine::json_parser
{

// using json = nlohmann::json;

// // help functions

// void
// parseString(std::string& to, const std::string& from, json& j);

// void
// parseInt(int& to, const std::string& from, json& j);

// // void
// // parseFloat(float& to, const std::string& from);

// void
// parseVec2(glm::vec2& vec2, const std::string& from, json& j);

// // models //

// struct ModelData
// {
//     std::string name;
//     std::string mesh;
//     std::string texture;
// };

// std::vector<ModelData>
// parseModels2D();

// // meshes //

// struct MeshData
// {
//     std::string name;
//     std::vector<uint32_t> inds;
//     std::vector<render::Vertex2DP1UV1> verts;
// };

// std::vector<MeshData>
// parseMeshes2D();

// // -- //

// // textures //

// struct TextureData
// {
//     std::string name;
//     std::string filename;
//     glm::vec2 scale;
//     glm::vec2 offset;
// };

// std::vector<TextureData>
// parseTextures();

} // namespace kusengine::json_parser

#endif // JSON_PARSER_HPP
