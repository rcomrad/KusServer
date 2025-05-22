#include "model.hpp"

#include <memory>
#include <vector>

namespace kusengine
{

void
Model::setMesh(const Mesh& mesh)
{
    m_mesh = mesh;
}

void
Model::setTexture(std::shared_ptr<const Texture> texture)
{
    m_texture = texture;
}
void
Model::bind(const vk::CommandBuffer& command_buffer,
            const vk::PipelineLayout& pipelayout) const
{
    m_texture->bind(command_buffer, pipelayout);
}

void
Model::pushMeshData(std::vector<UniversalVertexAttributes>& vertices,
                    std::vector<uint32_t>& indices) const
{
    m_mesh.pushData(vertices, indices);
}

bool
Model::compareData(const Model& other) const
{
    return m_mesh == other.m_mesh && *m_texture == *other.m_texture;
}

}; // namespace kusengine
