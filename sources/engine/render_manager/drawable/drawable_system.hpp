#ifndef DRAWABLE_SYSTEM_HPP
#define DRAWABLE_SYSTEM_HPP

#include "engine/render_manager/model/model_storage.hpp"
#include "engine/render_manager/swap_chain/swap_chain_frame.hpp"

#include "basic_drawable.hpp"

namespace kusengine
{
namespace render
{

template <typename DrawableT, typename MBBDType>
class DrawableSystem
{
public:
    using DrawableType = DrawableT;

    template <typename Iterator>
    void resetDrawables(Iterator begin, Iterator end);

    // void update(SwapChainFrame& frame) const;

    void bind(const vk::CommandBuffer& command_buffer) const;

    void draw(const vk::CommandBuffer& command_buffer,
              const vk::PipelineLayout& layout) const;

    const std::vector<MBBDType>& getMBDD() const& noexcept;

private:
    bool is_empty = true;

    ModelStorage<typename DrawableT::VertexType> m_model_storage;

    std::vector<MBBDType> mbdd_data_vector;
};

template <typename DrawableT, typename MBBDType>
template <typename Iterator>
void
DrawableSystem<DrawableT, MBBDType>::resetDrawables(Iterator begin,
                                                    Iterator end)
{
    uint32_t count = end - begin;
    mbdd_data_vector.resize(count);

    if (count != 0) is_empty = false;

    std::vector<std::pair<uint32_t, uint32_t>> inds(count);
    auto it = begin;
    for (uint32_t i = 0; i < count; i++)
    {
        auto& drawable = *((it++)->get());
        auto index     = drawable.pushModel(m_model_storage);

        inds[i].first  = i;
        inds[i].second = index;
    }
    std::sort(inds.begin(), inds.end(), [](const auto& left, const auto& right)
              { return left.second < right.second; });

    for (uint32_t i = 0; i < count; i++)
    {
        auto cor_index = inds[i].first;

        (begin + cor_index)->get()->linkData(&(mbdd_data_vector[i]));
        (begin + cor_index)->get()->updModelMatrix();
    }

    m_model_storage.fillBuffers();
}
// template <typename DrawableT, typename MBBDType>
// void
// DrawableSystem<DrawableT, MBBDType>::update(SwapChainFrame& frame) const
// {
//     frame.updateMBDD(mbdd_data_vector);
//     frame.updateUBO(m_ubo);
// }

template <typename DrawableT, typename MBBDType>
void
DrawableSystem<DrawableT, MBBDType>::bind(
    const vk::CommandBuffer& command_buffer) const
{
    if (is_empty) return;
    m_model_storage.bind(command_buffer);
}

template <typename DrawableT, typename MBBDType>
void
DrawableSystem<DrawableT, MBBDType>::draw(
    const vk::CommandBuffer& command_buffer,
    const vk::PipelineLayout& layout) const
{
    if (is_empty) return;
    m_model_storage.draw(command_buffer, layout);
}

template <typename DrawableT, typename MBBDType>
const std::vector<MBBDType>&
DrawableSystem<DrawableT, MBBDType>::getMBDD() const& noexcept
{
    return mbdd_data_vector;
}

}; // namespace render
}; // namespace kusengine

#endif // DRAWABLE_SYSTEM_HPP
