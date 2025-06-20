#ifndef RENDER_MANAGER_HPP
#define RENDER_MANAGER_HPP

#include "engine/render_manager/descriptors/descriptor_manager.hpp"
#include "engine/render_manager/instance/instance.hpp"
#include "engine/render_manager/swap_chain/swap_chain.hpp"
#include "renderer/render_way_storage.hpp"
#include "renderer/renderer.hpp"

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
    void draw(const Renderer& renderer);

private:
    int max_frames_in_flight;
    int frame_number;

    Instance m_instance;

    SwapChain m_swap_chain;

    RenderWayStorage m_render_way_storage;
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
