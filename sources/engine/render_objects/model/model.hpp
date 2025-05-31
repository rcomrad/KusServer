#ifndef MODEL_HPP
#define MODEL_HPP

#include "engine/render_objects/model/mesh/mesh.hpp"
#include "engine/textures/texture.hpp"

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

    Model& operator=(const Model& other) = default;

private:
    std::shared_ptr<const Mesh> m_mesh;
    std::shared_ptr<const Texture> m_texture;
};

// struct ModelEqual
// {
//     bool operator()(const Model& lhs, const Model& rhs) const;
// };

// template <>
// class std::hash<Model>
// {
//     void operator()();
// };

} // namespace kusengine
#endif // MODEL_HPP
