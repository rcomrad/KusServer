#ifndef RENDER_MANAGER_HPP
#define RENDER_MANAGER_HPP

//
#include "descriptors/descriptor_manager.hpp"
#include "instance/instance.hpp"
#include "renderer/renderer.hpp"
#include "swap_chain/swap_chain.hpp"
//
#include "camera/camera.hpp"
#include "commands/command_buffer.hpp"
#include "drawable/drawable_system_storage.hpp"
#include "drawable/drawable_usings.hpp"
#include "renderer/render_system.hpp"
#include "scene/basic_scene.hpp"
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
private:
    Camera2D m_camera2d;

    UBO m_ubo;
    // ----------------------- //
    //
    // ------ resources ------ //
public:

    const kusengine::render::Texture *const getTexture() const;

    // const Mesh* getMesh() const;

private:
    TextureManager m_texture_manager;
    // ----------------------- //
private:
    RenderManager();
};
}; // namespace render
}; // namespace kusengine

#endif // RENDER_MANAGER_HPP
