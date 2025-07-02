#ifndef RENDER_MANAGER_HPP
#define RENDER_MANAGER_HPP

//
#include "descriptors/descriptor_manager.hpp"
#include "instance/instance.hpp"
#include "swap_chain/swap_chain.hpp"
//
#include "camera/camera_manager.hpp"
#include "commands/command_buffer.hpp"
#include "drawable/drawable_system_storage.hpp"
#include "drawable/drawable_usings.hpp"
#include "dynamics_data/uniform_buffer_object.hpp"
#include "mesh/mesh_manager.hpp"
#include "renderer/render_system.hpp"
#include "scene/basic_scene.hpp"
#include "shaders/shader_manager.hpp"
#include "textures/texture_manager.hpp"

namespace kusengine
{
class Window;

namespace render
{

class RenderManager
{

public:
    static RenderManager& getInstance();

public:
    // --- init / shutdown --- //
    void init(const kusengine::Window& window);

    void shutdown();

private:
    // ----------------------- //
    //
    // --------- draw -------- //
public:
    // void registerScene(BasicScene* const basic_scene);

    void draw(BasicScene* const basic_scene);

private:
    int max_frames_in_flight;
    int frame_number;

    Instance m_instance;

    SwapChain m_swap_chain;

    RenderSystem m_render_system;

    DescriptorManager m_descriptor_manager;

    ShaderManager m_shader_manager;

    // ----------------------- //
    //
    // ------- resize -------- //

public:
    void resize(int x, int y);

private:
    // ----------------------- //
    //
    // ------- camera -------- //
public:
    CameraManager& camera();

private:
    CameraManager m_camera_manager;

    UBO m_ubo;
    // ----------------------- //
    //
    // ------ resources ------ //
public:
    template <typename ResT>
    struct ChooseResType
    {
    };

    template <typename ResT>
    const ResT* const getResource(ChooseResType<ResT>&& res_type,
                                  const std::string& key) const
    {
        return getResourceImpl(std::move(res_type), key);
    }

    // const Mesh* getMesh() const;

private:
    TextureManager m_texture_manager;
    MeshManager m_mesh_manager;

    const Texture* const getResourceImpl(
        ChooseResType<Texture>&& rs,
        const std::string& key) const; // texture

    // Meshes
    const Mesh<Vertex2DP1UV1>* const getResourceImpl(
        ChooseResType<Mesh<Vertex2DP1UV1>>&& rs,
        const std::string& key) const; // mesh<vertex 2d>

    const Mesh<Vertex3DP1UV1>* const getResourceImpl(
        ChooseResType<Mesh<Vertex3DP1UV1>>&& rs,
        const std::string& key) const; // mesh<vertex 3d>

    // ----------------------- //
private:
    RenderManager();
};
}; // namespace render
}; // namespace kusengine

#endif // RENDER_MANAGER_HPP
