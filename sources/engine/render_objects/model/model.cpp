#include "model.hpp"

#include <memory>
#include <vector>

namespace kusengine
{

int
Model::pushThis(std::vector<std::pair<Model, uint32_t>>& models)
{
    auto it = std::find_if(models.begin(), models.end(),
                           [this](const std::pair<Model, uint32_t>& other)
                           { return this->compareData(other.first); });

    int index = it - models.begin();

    if (it == models.end())
    {
        models.emplace_back(*this, 1u);
    }
    else
    {
        it->second += 1;
    }
    return index;
}

void
Model::setMesh(std::shared_ptr<const Mesh> mesh)
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
    m_mesh->pushData(vertices, indices);
}

bool
Model::compareData(const Model& other) const
{
    return *m_mesh == *other.m_mesh && *m_texture == *other.m_texture;
}

}; // namespace kusengine
