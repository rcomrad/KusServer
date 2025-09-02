#include "material_parser.hpp"

#include <fstream>

#include "engine/render_manager/material/material.hpp"

#include "parser_basic_functions.hpp"

namespace kusengine::parser
{

struct TextureZoneParseData
{
    std::string name;
    std::string texture_file;
    glm::vec2 offset;
    glm::vec2 scale;
};

void
to_json(nlohmann::json& j, const TextureZoneParseData& material)
{
    j = nlohmann::json{
        {"name",         material.name        },
        {"texture_file", material.texture_file},
        {"offset",       material.offset      },
        {"scale",        material.scale       }
    };
}

void
from_json(const nlohmann::json& j, TextureZoneParseData& material)
{
    j.at("name").get_to(material.name);
    j.at("texture_file").get_to(material.texture_file);
    j.at("offset").get_to(material.offset);
    j.at("scale").get_to(material.scale);
}

std::unordered_map<std::string, std::unique_ptr<render::Material>>
MaterialParser::parseTextureZones(const nlohmann::json& j,
                                  const render::TextureManager& texture_manager)
{
    std::unordered_map<std::string, std::unique_ptr<render::Material>> res;

    std::vector<TextureZoneParseData> texture_zones_data =
        j.get<std::vector<TextureZoneParseData>>();

    for (auto&& tz_data : texture_zones_data)
    {
        auto&& texture = texture_manager.getTexture(tz_data.texture_file);

        res[tz_data.name] = std::make_unique<render::TextureZoneMaterial>(
            render::TextureZone{.m_offset  = tz_data.offset,
                                .m_scale   = tz_data.scale,
                                .m_texture = texture});
    }

    return res;
}

void
MaterialParser::parse(const std::string& filename,
                      render::MaterialManager& material_manager,
                      const render::TextureManager& texture_manager)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    nlohmann::json j;
    file >> j;

    material_manager.setTextureZones(
        parseTextureZones(j["texture_zone_materials"], texture_manager));
}

} // namespace kusengine::parser
