#ifndef MESH_FACTORY_HPP
#define MESH_FACTORY_HPP
#include "engine/model/vertex/vertex.hpp"

#include "mesh.hpp"

namespace kusengine
{
class MeshFactory
{
public:
    static MeshFactory& getInstance();

    Mesh<UniversalVertex> createUniversalRectangleMesh(
        const glm::vec2& position,
        const glm::vec2& size, const glm::vec3& color);

private:
    MeshFactory() = default;
};

#define MESH_FACTORY MeshFactory::getInstance()

}; // namespace kusengine

#endif // MESH_FACTORY_HPP
