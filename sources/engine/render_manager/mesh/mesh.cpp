#include "mesh.hpp"

#include <exception>
namespace kusengine::render
{

void
Mesh::setInds(const std::vector<float>& inds)
{
    if (std::max(inds.begin(), inds.end()) >= m_vertices.size())
    {
        throw std::exception{"max index in inds for mesh is >= verts size"};
    }
    m_indices = inds;
}

}; // namespace kusengine::render
