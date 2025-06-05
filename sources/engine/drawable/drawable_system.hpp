#ifndef DRAWABLE_SYSTEM_HPP
#define DRAWABLE_SYSTEM_HPP

#include "engine/render_objects/model/model_storage.hpp"

#include "drawable.hpp"

namespace kusengine
{
class SwapChainFrame;

class DrawableSystem
{
public:
    // void add(Drawable* const NO_TEMPARARY);

    void add(const std::vector<std::shared_ptr<Drawable>>& NO_TEMPARARY);

    void generate();

    void updateMBDD(SwapChainFrame& frame) const;

    void draw(const vk::CommandBuffer& command_buffer,
              const vk::PipelineLayout& pipelayout,
              SwapChainFrame& frame) const;

private:
    ModelStorage m_model_storage;

    std::vector<std::shared_ptr<Drawable>> m_drawables;

    std::vector<MBDD> mbdd_data_vector;
};
}; // namespace kusengine

#endif // DRAWABLE_SYSTEM_HPP
