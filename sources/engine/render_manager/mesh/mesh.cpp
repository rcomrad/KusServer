#include "mesh.hpp"

#include <exception>
namespace kusengine::render
{

IMesh::IMesh(VertexType vt, int vert_byte_size)
    : m_vertex_type(vt), m_vertex_byte_size(vert_byte_size)
{
}

void
IMesh::setInds(const std::vector<uint32_t>& inds)
{
    m_indices = inds;
}

const Material*
IMesh::getMaterial() const noexcept
{
    return m_material;
}



}; // namespace kusengine::render
