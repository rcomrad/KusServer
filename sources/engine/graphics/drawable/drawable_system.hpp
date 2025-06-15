#ifndef DRAWABLE_SYSTEM_HPP
#define DRAWABLE_SYSTEM_HPP

#include "engine/graphics/models/model/model_storage.hpp"

#include "drawable.hpp"

namespace kusengine
{
class SwapChainFrame;

class DrawableSystem
{
public:
    // void add(Drawable* const NO_TEMPARARY);
    DrawableSystem();

    template <typename DerivedDrawable>
    void setDrawableVector(
        const std::vector<std::shared_ptr<DerivedDrawable>>& NO_TEMPARARY)
    {
        if (NO_TEMPARARY.size() > 0) is_empty = false;

        m_drawables.reserve(NO_TEMPARARY.size());
        for (int i = 0; i < NO_TEMPARARY.size(); ++i)
        {
            m_drawables.emplace_back(NO_TEMPARARY[i]);
        }
    }

    void generate();

    void updateMBDD(SwapChainFrame& frame) const;

    void draw(const vk::CommandBuffer& command_buffer,
              const vk::PipelineLayout& pipelayout,
              SwapChainFrame& frame) const;

private:
    bool is_empty;

    ModelStorage m_model_storage;

    std::vector<std::shared_ptr<Drawable>> m_drawables;

    std::vector<MBDD> mbdd_data_vector;
};
}; // namespace kusengine

#endif // DRAWABLE_SYSTEM_HPP
