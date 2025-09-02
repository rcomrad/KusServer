#include "pipeline_key.hpp"

namespace kusengine::render
{
bool
operator==(const PipelineKey& left, const PipelineKey& right)
{
    return left.model_upd_data_type == right.model_upd_data_type &&
           left.material_type == right.material_type &&
           left.vertex_type == right.vertex_type;
}
} // namespace kusengine::render
namespace std
{
size_t
hash<kusengine::render::PipelineKey>::operator()(
    const kusengine::render::PipelineKey& key) const noexcept
{
    size_t h1 =
        hash<decltype(key.model_upd_data_type)>{}(key.model_upd_data_type);
    size_t h2 = hash<decltype(key.vertex_type)>{}(key.vertex_type);
    size_t h3 = hash<decltype(key.material_type)>{}(key.material_type);

    return h1 ^ (h2 << 1) ^ (h3 << 2);
}
} // namespace std
