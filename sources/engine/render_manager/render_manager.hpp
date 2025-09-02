#ifndef RENDER_MANAGER_HPP
#define RENDER_MANAGER_HPP

//
#include "descriptors/descriptor_manager.hpp"
#include "instance/instance.hpp"
#include "swap_chain/swap_chain.hpp"
//
#include "camera/camera_manager.hpp"
#include "commands/command_buffer.hpp"
#include "dynamics_data/uniform_buffer_object.hpp"
#include "engine/scene/scene.hpp"
#include "mesh/mesh_manager.hpp"
#include "renderer/render_system.hpp"
#include "shaders/shader_manager.hpp"

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
    void setup(const kusengine::Window& window);

    void shutdown();

private:
    // ----------------------- //
    //
    // --------- draw -------- //
public:
    // void registerScene(BasicScene* const basic_scene);

    void render(Scene& scene);

private:
    int m_max_frames_in_flight;
    int m_current_frame_number;

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
    // ------ getters ------ //
public:
    const MeshManager& meshManager() const noexcept;

    const DescriptorManager& descriptorManager() const noexcept;

    int frameCount() const noexcept;

    int getCurrentFrameNumber() const noexcept;

private:
    MeshManager m_mesh_manager;

    MaterialManager m_material_manager;

    TextureManager m_texture_manager;

    // ----------------------- //
private:
    RenderManager();
};
}; // namespace render
}; // namespace kusengine

#endif // RENDER_MANAGER_HPP
