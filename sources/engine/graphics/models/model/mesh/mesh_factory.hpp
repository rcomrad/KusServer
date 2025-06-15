#ifndef MESH_FACTORY_HPP
#define MESH_FACTORY_HPP
#include "glm/vec2.hpp"

#include "mesh.hpp"

namespace kusengine
{
class MeshFactory
{
public:
    static MeshFactory& getInstance();

    std::shared_ptr<Mesh> getMesh(const std::vector<glm::vec2>& position_verts,
                                  const std::vector<glm::vec2>& texture_verts,
                                  const std::vector<uint32_t>& indices);

private:
    std::vector<std::shared_ptr<Mesh>> created_meshes;

    Mesh createMesh(const std::vector<glm::vec2>& position_verts,
                    const std::vector<glm::vec2>& texture_verts,
                    const std::vector<uint32_t>& indices);

    MeshFactory() = default;
};

#define MESH_FACTORY MeshFactory::getInstance()

}; // namespace kusengine

#endif // MESH_FACTORY_HPP
