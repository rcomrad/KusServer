#ifndef SIMPLE_MODEL_HPP
#define SIMPLE_MODEL_HPP

#include <vulkan/vulkan.hpp>

#include "engine/render_manager/mesh/mesh.hpp"

#include "bind_info.hpp"
#include "model.hpp"

namespace kusengine::render
{

template <typename Vertex_t, typename InstanceData_t>
class SimpleModel final : public Model<Vertex_t, InstanceData_t>
{
public:
    SimpleModel();

    void setMesh(const Mesh<Vertex_t>* const mesh);

    void pushTo(std::vector<std::pair<const Mesh<Vertex_t>*, int>>& meshes)
        const override;

private:
    const Mesh<Vertex_t>* m_mesh;
};

template <typename Vertex_t, typename InstanceData_t>
SimpleModel<Vertex_t, InstanceData_t>::SimpleModel()
    : Model<Vertex_t, InstanceData_t>(
          Model<Vertex_t, InstanceData_t>::Type::SIMPLE)
{
}

template <typename Vertex_t, typename InstanceData_t>
void
SimpleModel<Vertex_t, InstanceData_t>::setMesh(const Mesh<Vertex_t>* const mesh)
{
    m_mesh = mesh;
}

template <typename Vertex_t, typename InstanceData_t>
void
SimpleModel<Vertex_t, InstanceData_t>::pushTo(
    std::vector<std::pair<const Mesh<Vertex_t>*, int>>& meshes) const
{
    auto it = std::find_if(
        meshes.begin(), meshes.end(),
        [&mesh = m_mesh](const std::pair<const Mesh<Vertex_t>*, int>& other)
        { return mesh == other.first; });

    if (it != meshes.end())
    {
        it->second++;
    }
    else
    {
        meshes.emplace_back(std::make_pair(m_mesh, 1));
    }
}

// template <typename Vertex_t, typename InstanceData_t>
// void
// SimpleModel<Vertex_t, InstanceData_t>::pushTo(
//     std::vector<std::pair<const Mesh<Vertex_t>*, int>>& meshes) const
// {
//
// }

// template <typename Vertex_t, typename InstanceData_t>
// std::pair<const Mesh* const, int>
// SimpleModel::takeMeshes() const
// {
//     return std::make_pair<const Mesh* const, int>(m_mesh, 1);
// }

} // namespace kusengine::render

#endif // SIMPLE_MODEL_HPP
