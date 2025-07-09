#ifndef SIMPLE_MODEL_HPP
#define SIMPLE_MODEL_HPP

#include <vulkan/vulkan.hpp>

#include "engine/render_manager/mesh/mesh.hpp"

#include "model.hpp"

namespace kusengine::render
{
class SimpleModel final : public Model
{
public:
    SimpleModel();

    void setMesh(const Mesh* const mesh);

    std::pair<const Mesh* const, int> takeMeshes() const override;

    // void bind(const vk::CommandBuffer& command_buffer,
    //           const vk::PipelineLayout& pipelayout) const;

private:
    const Mesh* m_mesh;
};
} // namespace kusengine::render

#endif // SIMPLE_MODEL_HPP
