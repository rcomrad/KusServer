#include "model_2d_parser.hpp"

#include <fstream>
#include <iostream>

#include "utility/file_system/path_storage.hpp"

namespace kusengine
{

// void
// json_parser::parseString(std::string& to, const std::string& from, json& j)
// {
//     if (j.contains(from) && j[from].is_string())
//     {
//         to = j[from];
//     }
// }

// void
// json_parser::parseInt(int& to, const std::string& from, json& j)
// {
//     if (j.contains(from) && j[from].is_number_integer())
//     {
//         to = j[from];
//     }
// }

// void
// json_parser::parseVec2(glm::vec2& vec2, const std::string& from, json& j)
// {
//     vec2.x = vertJson[from]["x"].get<float>();
//     vec2.y = vertJson[from]["y"].get<float>();
// }

// std::vector<json_parser::ModelData>
// json_parser::parseModels2D()
// {
//     auto file_name_opt = util::PathStorage::getFolderPath("resource");

//     std::string filename = file_name_opt.value().data();
//     filename += "objects_data/2d/models_data/models.json";

//     std::ifstream input(filename);
//     json j_file;
//     input >> j_file;

//     std::vector<json_parser::ModelData> res;

//     try
//     {
//         if (j_file.contains("models") && j_file["models"].is_array())
//         {
//             for (const auto& model_json : j_file["models"])
//             {
//                 ModelData model_data;

//                 parseString(model_data.name, "name", model_json);
//                 parseString(model_data.mesh, "mesh", model_json);
//                 parseString(model_data.texture, "texture", model_json);

//                 res.emplace_back(model_data);
//             }
//         }
//     }
//     catch (const json::parse_error& e)
//     {
//         std::cerr << "JSON parse error: " << e.what() << std::endl;
//     }
//     catch (const json::type_error& e)
//     {
//         std::cerr << "JSON type error: " << e.what() << std::endl;
//     }
//     catch (const std::exception& e)
//     {
//         std::cerr << "Error: " << e.what() << std::endl;
//     }

//     return res;
// }

// std::vector<json_parser::MeshData>
// json_parser::parseMeshes2D()
// {
//     auto file_name_opt = util::PathStorage::getFolderPath("resource");

//     std::string filename = file_name_opt.value().data();
//     filename += "objects_data/2d/models_data/meshes.json";

//     std::ifstream input(filename);
//     json j;
//     input >> j;

//     std::vector<json_parser::MeshData> res;

//     try
//     {
//         if (j.find("meshes") != j.end())
//         {
//             for (const auto& meshJson : j["meshes"])
//             {
//                 MeshData mesh_data;
//                 parseString(mesh_data.name, "name", meshJson);

//                 for (const auto& vertJson : meshJson["verts"])
//                 {
//                     render::Vertex2DP1UV1 vertex;

//                     parseVec2(vertex.m_attributes.pos, "position", vertJson);
//                     parseVec2(vertex.m_attributes.uv, "uv", vertJson);

//                     mesh_data.verts.emplace_back(vertex);
//                 }

//                 for (const auto& index_j : meshJson["inds"])
//                 {
//                     int index;
//                     parseInt(index, "inds", index_j);
//                     mesh_data.inds.emplace_back(index);
//                 }

//                 res.emplace_back(mesh_data);
//             }
//         }
//     }
//     catch (const std::exception& e)
//     {
//         std::cerr << "Error parsing JSON: " << e.what() << std::endl;
//     }

//     return res;
// }

// std::vector<json_parser::TextureData>
// json_parser::parseTextures()
// {
//     auto file_name_opt = util::PathStorage::getFolderPath("resource");

//     std::string filename = file_name_opt.value().data();
//     filename += "objects_data/2d/models_data/textures.json";

//     std::ifstream input(filename);
//     json j_file;
//     input >> j_file;

//     std::vector<TextureData> res;

//     try
//     {
//         if (j_file.contains("textures") && j_file["textures"].is_array())
//         {
//             for (const auto& tex_json : j_file["textures"])
//             {

//                 TextureData texture_data;

//                 parseString(texture_data.name, "name", tex_json);
//                 parseString(texture_data.filename, "filename", tex_json);
//                 parseVec2(texture_data.offset, "offset", tex_json);
//                 parseVec2(texture_data.scale, "scale", tex_json);

//                 res.emplace_back(texture_data);
//             }
//         }
//     }
//     catch (const json::parse_error& e)
//     {
//         std::cerr << "JSON parse error: " << e.what() << std::endl;
//     }
//     catch (const json::type_error& e)
//     {
//         std::cerr << "JSON type error: " << e.what() << std::endl;
//     }
//     catch (const std::exception& e)
//     {
//         std::cerr << "Error: " << e.what() << std::endl;
//     }

//     return res;
// }

} // namespace kusengine
