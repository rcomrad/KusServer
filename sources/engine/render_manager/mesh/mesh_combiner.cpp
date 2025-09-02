#include "mesh_combiner.hpp"

#include <iostream>

#include "draw_info.hpp"
namespace kusengine::render
{
void
MeshCombiner::add(const IMesh* const mesh)
{
    auto it = std::find_if(m_meshes.begin(), m_meshes.end(),
                           [&m = mesh](const MeshAndIndices& other)
                           { return other.mesh == m; });

    if (it == m_meshes.end())
    {
        m_meshes.emplace_back(
            MeshAndIndices{.indices = {m_count}, .mesh = mesh});
    }
    else
    {
        it->indices.emplace_back(m_count);
    }
    m_count++;
}

std::vector<size_t>
MeshCombiner::fillBuffers(IndexBuffer& index_buffer,
                          GpuVertexBuffer& vertex_buffer,
                          std::vector<DrawInfo>& draw_info_vec) const
{
    draw_info_vec.resize(0);
    // sort by vert
    std::sort(m_meshes.begin(), m_meshes.end(),
              [](const MeshAndIndices& left, const MeshAndIndices& right)
              { return left.mesh->getVertType() < right.mesh->getVertType(); });
    //
    // sort by material
    std::sort(m_meshes.begin(), m_meshes.end(),
              [](const MeshAndIndices& left, const MeshAndIndices& right)
              {
                  if (left.mesh->getVertType() == right.mesh->getVertType())
                  {
                      return left.mesh->getMaterial() <
                             right.mesh->getMaterial();
                  }
                  return false;
              });
    //

    std::vector<size_t> mesh_order;
    mesh_order.reserve(m_count);

    std::vector<char> verts;
    std::vector<uint32_t> inds;

    size_t instance_shift = 0;
    size_t vertex_offset  = 0;
    size_t index_offset   = 0;

    for (int i = 0; i < m_meshes.size(); ++i)
    {
        DrawInfo di;

        // instance
        di.instance_count = m_meshes[i].indices.size();
        di.first_instance = instance_shift;
        instance_shift += di.instance_count;

        // types
        di.vertex_type = m_meshes[i].mesh->getVertType();
        di.material    = m_meshes[i].mesh->getMaterial();

        for (int j = 0; j < di.instance_count; ++j)
        {
            mesh_order.emplace_back(m_meshes[i].indices[j]);
        }

        // buffers and verts
        auto [vert_c, inds_c] = m_meshes[i].mesh->pushDataTo(verts, inds);

        di.vertex_count  = vert_c;
        di.vertex_offset = vertex_offset;
        vertex_offset += di.vertex_count;

        // inds
        di.index_count = inds_c;
        di.first_index = index_offset;
        index_offset += inds_c;

        draw_info_vec.emplace_back(di);
    }

    vertex_buffer.setData(verts.data(), verts.size());

    index_buffer.setData(inds.data(), inds.size() * sizeof(uint32_t));

    return mesh_order;
}

} // namespace kusengine::render
