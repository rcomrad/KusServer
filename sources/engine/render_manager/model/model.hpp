#ifndef MODEL_HPP
#define MODEL_HPP

#include "engine/render_manager/mesh/mesh.hpp"
#include "engine/render_manager/textures/texture.hpp"

namespace kusengine
{
namespace render
{

template <typename VertexType>
class Model
{
public:
    Model() = default;

    void setMesh(const Mesh<VertexType>* const mesh_ptr);

    void setTexture(const Texture* const texture_ptr);

    void bindTexture(const vk::CommandBuffer& command_buffer,
                     const vk::PipelineLayout& pipelayout) const;

    bool compareData(const Model<VertexType>&) const;

    void pushMeshData(std::vector<typename VertexType::Attributes>&,
                      std::vector<uint32_t>&) const;

    int pushThis(std::vector<std::pair<Model<VertexType>, uint32_t>>&) const;

private:
    const Mesh<VertexType>* m_mesh;
    const Texture* m_texture;
};

template <typename VertexType>
int
Model<VertexType>::pushThis(
    std::vector<std::pair<Model<VertexType>, uint32_t>>& models) const
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

template <typename VertexType>
void
Model<VertexType>::setMesh(const Mesh<VertexType>* const mesh_ptr)
{
    m_mesh = mesh_ptr;
}

template <typename VertexType>
void
Model<VertexType>::setTexture(const Texture* const texture_ptr)
{
    m_texture = texture_ptr;
}

template <typename VertexType>
void
Model<VertexType>::bindTexture(const vk::CommandBuffer& command_buffer,
                               const vk::PipelineLayout& pipelayout) const
{
    m_texture->bind(command_buffer, pipelayout);
}

template <typename VertexType>
void
Model<VertexType>::pushMeshData(
    std::vector<typename VertexType::Attributes>& vertices,
    std::vector<uint32_t>& indices) const
{
    m_mesh->pushData(vertices, indices);
}

template <typename VertexType>
bool
Model<VertexType>::compareData(const Model& other) const
{
    return *m_mesh == *other.m_mesh && *m_texture == *other.m_texture;
}

}; // namespace render
}; // namespace kusengine
#endif // MODEL_HPP
