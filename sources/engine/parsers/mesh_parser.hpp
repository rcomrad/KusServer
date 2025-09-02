#ifndef MESH_PARSER_HPP
#define MESH_PARSER_HPP
#include <string>

#include "engine/render_manager/mesh/mesh_manager.hpp"
namespace kusengine::parser
{
class MeshParser
{
public:
    std::unordered_map<std::string, std::unique_ptr<render::IMesh>> parse(
        const std::string& filename,
        render::MeshManager& mesh_manager);

private:
    template <const char* vertex_type>
    void parseVerts();
};

extern template void
MeshParser::parseVerts<"P2DUV">();

} // namespace kusengine::parser

#endif // MESH_PARSER_HPP
