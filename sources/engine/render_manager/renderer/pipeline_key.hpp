
#ifndef PIPELINE_KEY_HPP
#define PIPELINE_KEY_HPP

#include <unordered_map>

#include "engine/render_manager/material/material.hpp"
#include "engine/render_manager/model/model_data/model_upd_data.hpp"
#include "engine/render_manager/vertex/vertex.hpp"

namespace kusengine::render
{
struct PipelineKey
{
    VertexType vertex_type;
    ModelUpdData::Type model_upd_data_type;
    Material::Type material_type;
};

bool
operator==(const PipelineKey& left, const PipelineKey& right);

} // namespace kusengine::render

namespace std
{
template <>
struct hash<kusengine::render::PipelineKey>
{
    size_t operator()(const kusengine::render::PipelineKey& key) const noexcept;
};
} // namespace std

#endif // PIPELINE_KEY_HPP
