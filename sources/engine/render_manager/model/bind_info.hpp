#ifndef BIND_INFO_HPP
#define BIND_INFO_HPP

#include "engine/render_manager/dynamics_data/instancing_data/instance_data.hpp"
#include "engine/render_manager/material/material.hpp"
#include "engine/render_manager/renderer/pipeline_key.hpp"
#include "engine/render_manager/vertex/vertex.hpp"

namespace kusengine::render
{

struct BindPipelineInfo
{
    PipelineKey pipeline_key;
};

struct DrawInfo
{
    uint32_t index_count;
    uint32_t instance_count;
    uint32_t first_index;
    uint32_t vertex_offset;
    uint32_t first_instance;
};
} // namespace kusengine::render

#endif // BIND_INFO_HPP
