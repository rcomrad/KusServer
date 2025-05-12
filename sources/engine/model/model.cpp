#include "model.hpp"

namespace kusengine
{
void
Model::setMesh(const Mesh& mesh)
{
    m_mesh = mesh;
}
void
Model::setMesh(Mesh&& mesh)
{
    m_mesh = mesh;
}

const Mesh&
Model::getMesh() const
{
    return m_mesh;
}

void
Model::setTexture(const std::shared_ptr<Texture>& texture)
{
    m_texture = texture;
}

const vk::DescriptorSet&
Model::getTextureDescriptorSet() const
{
    return m_texture->getDescriptorSet();
}
}; // namespace kusengine
