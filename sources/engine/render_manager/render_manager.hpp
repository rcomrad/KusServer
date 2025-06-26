#ifndef RENDER_MANAGER_HPP
#define RENDER_MANAGER_HPP

//
#include "descriptors/descriptor_manager.hpp"
#include "instance/instance.hpp"
#include "renderer/renderer.hpp"
#include "swap_chain/swap_chain.hpp"
//
#include "drawable/drawable_system_storage.hpp"
#include "drawable/drawable_usings.hpp"
#include "renderer/render_system.hpp"
#include "scene/basic_scene.hpp"

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
    void registerScene(BasicScene* const basic_scene);

    void draw(BasicScene* const basic_scene);

private:
    int max_frames_in_flight;
    int frame_number;

    Instance m_instance;

    SwapChain m_swap_chain;

    RenderSystem m_render_system;

    DrawableSystemStorage<DrawableSystem_P1UV1_TRS> m_drawable_system_storage;

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
    // ----------------------- //
    //
    // ------- buffers ------- //
public:
private:
    // ----------------------- //
private:
    RenderManager();
};
}; // namespace render
}; // namespace kusengine

#endif // RENDER_MANAGER_HPP
