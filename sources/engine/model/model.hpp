#ifndef MODEL_HPP
#define MODEL_HPP

#include "engine/model/mesh/mesh.hpp"
#include "engine/model/vertex/vertex.hpp"
#include "engine/textures/texture.hpp"

namespace kusengine
{
class Model
{
public:
    void setMesh(const Mesh& mesh);
    void setMesh(Mesh&& mesh);

    const Mesh& getMesh() const;

    void setTexture(const std::shared_ptr<Texture>& texture);

    const vk::DescriptorSet& getTextureDescriptorSet() const;

private:
    Mesh m_mesh;
    std::shared_ptr<const Texture> m_texture;
};

}; // namespace kusengine

#endif // MODEL_HPP
