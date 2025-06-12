#include "drawable_system.hpp"

#include "engine/graphics/renderer/swap_chain_frame.hpp"
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

DrawableSystem::DrawableSystem() : is_empty(true)
{
}

void
DrawableSystem::updateMBDD(SwapChainFrame& frame) const
{
    if (is_empty) return;
    frame.updateMBDD(mbdd_data_vector);
}

void
DrawableSystem::setDrawableVector(
    const std::vector<std::shared_ptr<Drawable>>& NO_TEMPARARY)
{
    if (NO_TEMPARARY.size() > 0) is_empty = false;
    m_drawables = NO_TEMPARARY;
}

void
DrawableSystem::generate()
{
    if (is_empty) return;
    mbdd_data_vector.resize(m_drawables.size());
    for (int i = 0; i < m_drawables.size(); ++i)
    {
        auto& drawable = m_drawables[i];
        drawable->pushModel(m_model_storage);
        drawable->linkData(&mbdd_data_vector[i]);
        drawable->updModelMatrix();
    }
    m_model_storage.fillBuffers();
}

void
DrawableSystem::draw(const vk::CommandBuffer& command_buffer,
                     const vk::PipelineLayout& pipelayout,
                     SwapChainFrame& frame) const
{
    if (is_empty) return;
    m_model_storage.bind(command_buffer);

    m_model_storage.draw(command_buffer, pipelayout);
}
}; // namespace kusengine
