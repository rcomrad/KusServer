#ifndef COMPLEX_MODEL_HPP
#define COMPLEX_MODEL_HPP

#include <vulkan/vulkan.hpp>

#include "engine/render_manager/mesh/multi_mesh.hpp"

#include "model.hpp"

namespace kusengine::render
{
class ComplexModel final : public Model
{
public:
    ComplexModel();

    void setMultiMesh(const MultiMesh* const multi_mesh);

    std::pair<const Mesh* const, int> takeMeshes() const override;

private:
    const MultiMesh* m_multi_mesh;
};
} // namespace kusengine::render

#endif // COMPLEX_MODEL_HPP
