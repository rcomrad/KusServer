#include "multi_mesh.hpp"

namespace kusengine::render
{

size_t
MultiMesh::size() const noexcept
{
    return m_meshes.size();
}

const Mesh* const
MultiMesh::get() const noexcept
{
    return m_meshes.data();
}

}; // namespace kusengine::render
