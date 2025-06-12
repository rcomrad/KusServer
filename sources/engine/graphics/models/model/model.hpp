#ifndef MODEL_HPP
#define MODEL_HPP

#include "engine/graphics/models/model/mesh/mesh.hpp"
#include "engine/graphics/textures/texture.hpp"

namespace kusengine
{
class Model
{
public:
    void setMesh(std::shared_ptr<const Mesh> mesh);

    void setTexture(std::shared_ptr<const Texture> texture);

    void pushMeshData(std::vector<UniversalVertexAttributes>&,
                      std::vector<uint32_t>&) const;

    void bind(const vk::CommandBuffer& command_buffer,
              const vk::PipelineLayout& pipelayout) const;

    bool compareData(const Model&) const;

    int pushThis(std::vector<std::pair<Model, uint32_t>>&) const;

private:
    std::shared_ptr<const Mesh> m_mesh;
    std::shared_ptr<const Texture> m_texture;
};

} // namespace kusengine
#endif // MODEL_HPP
