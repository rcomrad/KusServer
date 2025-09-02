#ifndef DRAW_INFO_HPP
#define DRAW_INFO_HPP

#include "engine/render_manager/material/material.hpp"
#include "engine/render_manager/vertex/vertex.hpp"
namespace kusengine::render
{
struct DrawInfo
{
    const Material* material;
    VertexType vertex_type;
    uint32_t vertex_count;
    uint32_t instance_count;
    uint32_t vertex_offset;
    uint32_t first_instance;
    uint32_t index_count;
    uint32_t first_index;
};
}; // namespace kusengine::render

#endif // DRAW_INFO_HPP
