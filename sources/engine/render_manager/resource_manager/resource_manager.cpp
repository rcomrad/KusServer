#include "resource_manager.hpp"

namespace kusengine::render
{
void
ResourceManager::load(const DescriptorManager& desc_manager)
{
    m_mesh_manager.loadMeshes();
    m_texture_manager.loadTextures(desc_manager);
}

const MeshManager&
ResourceManager::meshes() const noexcept
{
    return m_mesh_manager;
}

const TextureManager&
ResourceManager::textures() const noexcept
{
    return m_texture_manager;
}

} // namespace kusengine::render
