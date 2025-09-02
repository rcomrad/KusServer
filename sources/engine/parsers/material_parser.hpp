#ifndef MATERIAL_PARSER_HPP
#define MATERIAL_PARSER_HPP
#include <nlohmann/json.hpp>

#include "engine/render_manager/material/material_manager.hpp"

namespace kusengine::parser
{

class MaterialParser
{
public:
    void parse(const std::string& filename,
               render::MaterialManager& material_manager,
               const render::TextureManager& texture_manager);

private:
    std::unordered_map<std::string, std::unique_ptr<render::Material>>
    parseTextureZones(const nlohmann::json& j,
                      const render::TextureManager& texture_manager);
};

} // namespace kusengine::parser

#endif // MATERIAL_PARSER_HPP
