#ifndef RENDER_MANAGER_HPP
#define RENDER_MANAGER_HPP

// universal drawable system
#include "engine/render_manager/drawable/basic_drawable.hpp"
#include "engine/render_manager/drawable/drawable_system.hpp"
#include "engine/render_manager/drawable/drawable_system_storage.hpp"
#include "engine/render_manager/drawable/universal/universal_drawable.hpp"
#include "engine/render_manager/dynamics_data/mbddi_buffer/mbdd_structs.hpp"
#include "engine/render_manager/dynamics_data/uniform_buffer_object.hpp"
//
#include "engine/render_manager/descriptors/descriptor_manager.hpp"
#include "engine/render_manager/instance/instance.hpp"
#include "engine/render_manager/swap_chain/swap_chain.hpp"
#include "renderer/render_way_storage.hpp"
#include "renderer/renderer.hpp"
//
namespace kusengine
{
class Window;

namespace render
{

using UniversalDrawableSystem =
    DrawableSystem<UniversalDrawable, UniversalMBDD, UBO>;

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
    void draw();

private:
    int max_frames_in_flight;
    int frame_number;

    Instance m_instance;

    SwapChain m_swap_chain;

    RenderWayStorage m_render_way_storage;

    DrawableSystemStorage<UniversalDrawableSystem>
        m_universal_drawable_system_storage;

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
