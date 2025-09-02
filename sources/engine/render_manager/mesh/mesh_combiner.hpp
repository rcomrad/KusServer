#ifndef MESH_COMBINER_HPP
#define MESH_COMBINER_HPP

#include <list>
#include <map>

#include "engine/render_manager/buffers/gpu_buffer.hpp"
#include "engine/render_manager/buffers/index_buffer.hpp"

#include "draw_info.hpp"
#include "mesh.hpp"

namespace kusengine::render
{
class MeshCombiner
{
public:
    void add(const IMesh* const mesh);

    std::vector<size_t> fillBuffers(IndexBuffer& m_index_buffer,
                                    GpuVertexBuffer& m_vertex_buffer,
                                    std::vector<DrawInfo>& draw_info_vec) const;

private:
    struct MeshAndIndices
    {
        std::vector<size_t> indices;
        const IMesh* mesh;
    };

    size_t m_count = 0;

    mutable std::vector<MeshAndIndices> m_meshes;
};
} // namespace kusengine::render

#endif // MESH_COMBINER_HPP
