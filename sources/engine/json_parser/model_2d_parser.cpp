#include "model_2d_parser.hpp"

#include <fstream>
#include <iostream>

#include "utility/file_system/path_storage.hpp"

using json = nlohmann::json;

namespace kusengine
{

std::vector<json_parser::ModelData>
json_parser::parseModels2D()
{
    auto file_name_opt = util::PathStorage::getFolderPath("resource");

    std::string filename = file_name_opt.value().data();
    filename += "objects_data/2d/models_data/models.json";

    std::ifstream input(filename);
    json j_file;
    input >> j_file;

    std::vector<json_parser::ModelData> res;

    try
    {
        if (j_file.contains("models") && j_file["models"].is_array())
        {
            for (const auto& model_json : j_file["models"])
            {
                if (model_json.contains("name") &&
                    model_json["name"].is_string())
                {

                    json_parser::ModelData model_data;
                    if (model_json.contains("mesh") &&
                        model_json["mesh"].is_string())
                    {
                        model_data.mesh = model_json["mesh"];
                    }

                    if (model_json.contains("texture") &&
                        model_json["texture"].is_string())
                    {
                        model_data.texture = model_json["texture"];
                    }

                    res.emplace_back(model_data);
                }
            }
        }
    }
    catch (const json::parse_error& e)
    {
        std::cerr << "JSON parse error: " << e.what() << std::endl;
    }
    catch (const json::type_error& e)
    {
        std::cerr << "JSON type error: " << e.what() << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return res;
}

std::vector<json_parser::MeshData>
json_parser::parseMeshes2D()
{
    auto file_name_opt = util::PathStorage::getFolderPath("resource");

    std::string filename = file_name_opt.value().data();
    filename += "objects_data/2d/models_data/meshes.json";

    std::ifstream input(filename);
    json j;
    input >> j;

    std::vector<json_parser::MeshData> res;

    try
    {
        if (j.find("meshes") != j.end())
        {
            for (const auto& meshJson : j["meshes"])
            {
                MeshData mesh_data;
                mesh_data.name = meshJson["name"].get<std::string>();

                // Парсим вершины
                for (const auto& vertJson : meshJson["verts"])
                {
                    render::Vertex2DP1UV1 vertex;
                    vertex.m_attributes.pos.x =
                        vertJson["position"]["x"].get<float>();
                    vertex.m_attributes.pos.y =
                        vertJson["position"]["y"].get<float>();
                    vertex.m_attributes.uv.x =
                        vertJson["uv_coords"]["x"].get<float>();
                    vertex.m_attributes.uv.y =
                        vertJson["uv_coords"]["y"].get<float>();

                    mesh_data.verts.emplace_back(vertex);
                }

                for (const auto& index : meshJson["inds"])
                {
                    mesh_data.inds.emplace_back(index.get<uint32_t>());
                }

                res.emplace_back(mesh_data);
            }
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error parsing JSON: " << e.what() << std::endl;
    }

    return res;
}

std::vector<json_parser::TextureData>
json_parser::parseTextures()
{
    auto file_name_opt = util::PathStorage::getFolderPath("resource");

    std::string filename = file_name_opt.value().data();
    filename += "objects_data/2d/models_data/textures.json";

    std::ifstream input(filename);
    json j_file;
    input >> j_file;

    std::vector<TextureData> res;

    try
    {
        if (j_file.contains("textures") && j_file["textures"].is_array())
        {
            for (const auto& tex_json : j_file["textures"])
            {
                if (tex_json.contains("name") && tex_json["name"].is_string())
                {

                    TextureData texture_data;

                    if (tex_json.contains("filename") &&
                        tex_json["filename"].is_string())
                    {
                        texture_data.filename = tex_json["filename"];
                    }

                    if (tex_json.contains("name") &&
                        tex_json["name"].is_string())
                    {
                        texture_data.name = tex_json["name"];
                    }

                    if (tex_json.contains("uv_coords") &&
                        tex_json["uv_coords"].is_array())
                    {
                        glm::vec2 coords;
                        for (const auto& uv_json : tex_json["uv_coords"])
                        {
                            if (uv_json.contains("x") &&
                                uv_json["x"].is_number())
                            {
                                coords.x = uv_json["x"];
                            }

                            if (uv_json.contains("y") &&
                                uv_json["y"].is_number())
                            {
                                coords.y = uv_json["y"];
                            }

                            texture_data.uv_coords.push_back(coords);
                        }
                    }
                    res.emplace_back(texture_data);
                }
            }
        }
    }
    catch (const json::parse_error& e)
    {
        std::cerr << "JSON parse error: " << e.what() << std::endl;
    }
    catch (const json::type_error& e)
    {
        std::cerr << "JSON type error: " << e.what() << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return res;
}

} // namespace kusengine
