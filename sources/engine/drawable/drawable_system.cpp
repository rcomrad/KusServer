#include "drawable_system.hpp"

#include "engine/gui/button.hpp"
#include "engine/renderer/swap_chain_frame.hpp"
namespace kusengine
{
// void
// DrawableSystem::add(Drawable* const no_temparary_drawable)
// {
//     if (no_temparary_drawable)
//     {
//         m_drawables.emplace_back(no_temparary_drawable);
//     }
// }

void
DrawableSystem::updateMBDD(SwapChainFrame& frame) const
{
    frame.updateMBDD(mbdd_data_vector);
}

void
DrawableSystem::add(const std::vector<std::shared_ptr<Drawable>>& NO_TEMPARARY)
{
    m_drawables = NO_TEMPARARY;
    // m_drawables.reserve(no_temparary_drawables->size() + m_drawables.size());

    // for (int i = 0; i < no_temparary_drawables->size(); ++i)
    // {
    //     add(no_temparary_drawables->operator[](i).get());
    // }

    // m_drawables.emplace_back(
    //     std::make_shared<Button>(glm::vec2{10.f, 2.f},
    //     glm::vec2{20.f, 60.f}));
}

void
DrawableSystem::generate()
{
    mbdd_data_vector.resize(m_drawables.size());
    for (int i = 0; i < m_drawables.size(); ++i)
    {
        auto& drawable = m_drawables[i];
        drawable->pushModel(m_model_storage);
        drawable->linkData(&mbdd_data_vector[i]);
        drawable->upd();
    }
    m_model_storage.fillBuffers();
}

void
DrawableSystem::draw(const vk::CommandBuffer& command_buffer,
                     const vk::PipelineLayout& pipelayout,
                     SwapChainFrame& frame) const
{
    m_model_storage.bind(command_buffer);

    m_model_storage.draw(command_buffer, pipelayout);
}
}; // namespace kusengine
