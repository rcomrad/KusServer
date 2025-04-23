#ifndef MESH_STORAGE__HPP
#define MESH_STORAGE__HPP

#include <iostream>

#include "engine/buffers/index_buffer.hpp"
#include "engine/buffers/vertex_buffer.hpp"
#include "engine/device/device.hpp"

#include "mesh.hpp"

namespace kusengine
{
enum class MeshType
{
    TRIANGLE,
    RECTANGLE
};

template <typename _VertexType>
class MeshStorage
{
public:
    MeshStorage() = default;

    void setVertices(MeshType type, const std::vector<_VertexType>& vertices);

    void setVertices(MeshType type,
                     const std::initializer_list<_VertexType>& vertices);

    void setIndices(MeshType type, const std::vector<uint32_t>& indices);

    void draw(const vk::CommandBuffer& command_buffer) const;

    void fillBuffers();

private:
    void calculateCounts();

    struct MeshInfo
    {
        Mesh<_VertexType> mesh;

        uint32_t vertex_offset;
        uint32_t index_offset;
    };

    bool is_buffer_filled;

    std::unordered_map<MeshType, MeshInfo> m_mesh_storage;

    // Vertices

    VertexBuffer m_vertex_buffer;

    size_t m_vertex_count;

    // Indices

    IndexBuffer m_index_buffer;

    size_t m_index_count;
};

template <typename _VertexType>
void
MeshStorage<_VertexType>::setVertices(MeshType type,
                                      const std::vector<_VertexType>& vertices)
{
    m_mesh_storage[type].mesh.setVertices(vertices);
    is_buffer_filled = false;
}

template <typename _VertexType>
void
MeshStorage<_VertexType>::setVertices(
    MeshType type,
    const std::initializer_list<_VertexType>& vertices)
{
    m_mesh_storage[type].mesh.setVertices(vertices);
    is_buffer_filled = false;
}

template <typename _VertexType>
void
MeshStorage<_VertexType>::setIndices(MeshType type,
                                     const std::vector<uint32_t>& indices)
{
    m_mesh_storage[type].mesh.setIndices(indices);
    is_buffer_filled = false;
}

template <typename _VertexType>
void
MeshStorage<_VertexType>::draw(const vk::CommandBuffer& command_buffer) const
{
    if (!is_buffer_filled)
    {
        std::cerr << "Fill buffers after setting vertices\n";
        return;
    }
    m_vertex_buffer.bind(command_buffer);
    m_index_buffer.bind(command_buffer, 0);
    m_index_buffer.draw(command_buffer, m_index_count, 0, 0);
}

template <typename _VertexType>
void
MeshStorage<_VertexType>::calculateCounts()
{
    m_vertex_count = 0;
    m_index_count  = 0;
    for (auto it = m_mesh_storage.begin(); it != m_mesh_storage.end(); ++it)
    {
        m_vertex_count += it->second.mesh.vertexCount();
        m_index_count += it->second.mesh.indexCount();
    }
}

template <typename _VertexType>
void
MeshStorage<_VertexType>::fillBuffers()
{
    calculateCounts();

    std::vector<float> m_vertex_data;
    std::vector<uint32_t> m_index_data;

    auto count_floats = _VertexType::countFloats();
    m_vertex_data.resize(m_vertex_count * count_floats);
    m_index_data.resize(m_index_count);

    size_t vertex_offset = 0;
    size_t index_offset  = 0;

    for (auto it = m_mesh_storage.begin(); it != m_mesh_storage.end(); ++it)
    {
        // Vertices
        it->second.vertex_offset = vertex_offset;
        auto count_vertex        = it->second.mesh.vertexCount();

        auto vertdata = it->second.mesh.verticesData();

        std::copy(vertdata, vertdata + count_vertex * count_floats,
                  m_vertex_data.data() + vertex_offset);

        vertex_offset += count_vertex * count_floats;

        // Indices

        it->second.index_offset = index_offset;

        auto count_index = it->second.mesh.indexCount();

        auto inddata = it->second.mesh.indicesData();

        std::copy(inddata, inddata + count_index,
                  m_index_data.data() + index_offset);

        index_offset += count_index;
    }
    m_vertex_buffer.setVertices(m_vertex_data);
    m_index_buffer.setIndices(m_index_data);
    is_buffer_filled = true;
}

}; // namespace kusengine

#endif // MESH_STORAGE__HPP
