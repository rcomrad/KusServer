#ifndef MESH_PARSER_HPP
#define MESH_PARSER_HPP
#include <string>

#include "engine/render_manager/mesh/mesh_manager.hpp"
namespace kusengine::parser
{
class MeshParser
{
public:
    void parse(const std::string& filename,
               render::MeshManager& mesh_manager,
               const render::MaterialManager& material_manager);

private:
};

} // namespace kusengine::parser

#endif // MESH_PARSER_HPP
