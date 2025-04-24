#ifndef SCENE_HPP
#define SCENE_HPP

#include "engine/mesh/mesh_storage.hpp"
#include "engine/mesh/vertex.hpp"

namespace kusengine
{
class Scene
{
public:
    Scene() = default;

    void create();

    void draw(const vk::CommandBuffer& command_buffer) const;

private:
    MeshStorage<UniversalVertex> m_mesh_storage;
};

}; // namespace kusengine

#endif // SCENE_HPP
