#include "complex_model.hpp"

namespace kusengine::render
{
ComplexModel::ComplexModel() : Model(Type::COMPLEX)
{
}

void
ComplexModel::setMultiMesh(const MultiMesh* const multi_mesh)
{
    m_multi_mesh = multi_mesh;
}

std::pair<const Mesh* const, int>
ComplexModel::takeMeshes() const
{
    return std::make_pair<const Mesh* const, int>(m_multi_mesh.get(),
                                                  m_multi_mesh.size());
}

} // namespace kusengine::render
