#ifndef MODEL_COMBINER_HPP
#define MODEL_COMBINER_HPP
#include <engine/render_manager/buffers/gpu_buffer.hpp>
#include <engine/render_manager/buffers/index_buffer.hpp>

#include <memory>
#include <vector>

#include "model.hpp"
namespace kusengine::render
{

class ModelCombiner
{
public:
    void combine(const std::vector<std::unique_ptr<Model>>& models);

private:
    // void sortByMaterial(std::vector<std::unique_ptr<Model>>& models) const;

    GpuVertexBuffer m_vertex_buffer;
    IndexBuffer m_index_buffer;
};
} // namespace kusengine::render

#endif // MODEL_COMBINER_HPP
