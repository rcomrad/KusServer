#include "simple_model.hpp"

namespace kusengine::render
{

SimpleModel::SimpleModel() : Model(Type::SIMPLE)
{
}

void
SimpleModel::setMesh(const Mesh* const mesh)
{
    m_mesh = mesh;
}

std::pair<const Mesh* const, int>
SimpleModel::takeMeshes() const
{
    return std::make_pair<const Mesh* const, int>(m_mesh, 1);
}

// void
// SimpleModel::bind(const vk::CommandBuffer& command_buffer,
//                   const vk::PipelineLayout& pipelayout) const
// {
//     m_mesh->
// }
} // namespace kusengine::render
