#ifndef VERTS_ATTRIBUTES_PARSERS_FUNCS_HPP
#define VERTS_ATTRIBUTES_PARSERS_FUNCS_HPP
#include "engine/render_manager/vertex/vertex_p2d_uv.hpp"
#include "engine/render_manager/vertex/vertex_p3d_uv.hpp"

#include "parser_basic_functions.hpp"

namespace nlohmann
{

template <>
struct adl_serializer<kusengine::render::VertexP2DUV>
{
    static void to_json(json& j, const kusengine::render::VertexP2DUV& vertex)
    {
        j = json{
            {"pos", vertex.getPos()},
            {"uv",  vertex.getUV() }
        };
    }

    static void from_json(const json& j, kusengine::render::VertexP2DUV& vertex)
    {
        glm::vec2 pos, uv;
        j.at("pos").get_to(pos);
        j.at("uv").get_to(uv);

        vertex.setPosition(pos);
        vertex.setUV(uv);
    }
};

template <>
struct adl_serializer<std::vector<kusengine::render::VertexP2DUV>>
{
    static void to_json(
        json& j,
        const std::vector<kusengine::render::VertexP2DUV>& vertices)
    {
        j = nlohmann::json::array();
        j.get_ref<nlohmann::json::array_t&>().reserve(vertices.size());

        for (const auto& v : vertices)
        {
            j.push_back(v);
        }
    }

    static void from_json(const json& j,
                          std::vector<kusengine::render::VertexP2DUV>& vertices)
    {
        vertices.clear();

        for (const auto& element : j)
        {
            vertices.push_back(element.get<kusengine::render::VertexP2DUV>());
        }
    }
};

template <>
struct adl_serializer<kusengine::render::P3DUV>
{
    // static void to_json(json& j, const kusengine::render::P3DUV& vertex)
    // {
    //     j = json{
    //         {"pos", vertex.pos},
    //         {"uv",  vertex.uv }
    //     };
    // }

    // static void from_json(const json& j, kusengine::render::P3DUV& vertex)
    // {
    //     j.at("pos").get_to(vertex.pos);
    //     j.at("uv").get_to(vertex.uv);
    // }
};

} // namespace nlohmann
#endif // VERTS_ATTRIBUTES_PARSERS_FUNCS_HPP
