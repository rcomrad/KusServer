#ifndef DRAWABLE_SYSTEM_HPP
#define DRAWABLE_SYSTEM_HPP

#include "engine/render_manager/model/model_storage.hpp"
#include "engine/render_manager/swap_chain/swap_chain_frame.hpp"

#include "basic_drawable.hpp"

namespace kusengine
{
namespace render
{

template <typename DrawableType_, typename MBBDType, typename UBOType>
class DrawableSystem
{
public:

    DrawableSystem() = default;

    template <typename Iterator>
    void resetDrawables(Iterator begin, Iterator end);

    void update(SwapChainFrame& frame) const;

    void draw(const vk::CommandBuffer& command_buffer,
              const vk::PipelineLayout& pipelayout,
              SwapChainFrame& frame) const;

private:
    bool is_empty;

    UBOType m_ubo;

    ModelStorage<typename DrawableType_::VertexType> m_model_storage;

    std::vector<MBBDType> mbdd_data_vector;
};

template <typename DrawableType_, typename MBBDType, typename UBOType>
template <typename Iterator>
void
DrawableSystem<DrawableType_, MBBDType, UBOType>::resetDrawables(Iterator begin,
                                                                Iterator end)
{
    uint32_t count = end - begin;
    mbdd_data_vector.resize(count);

    std::vector<std::pair<uint32_t, uint32_t>> inds(count);
    auto it = begin;
    for (uint32_t i = 0; i < count; i++)
    {
        auto& drawable = (it++).get();
        auto index     = drawable->pushModel(m_model_storage);

        inds[i].first  = i;
        inds[i].second = index;
    }
    std::sort(inds.begin(), inds.end(), [](const auto& left, const auto& right)
              { return left.second < right.second; });

    for (uint32_t i = 0; i < count; i++)
    {
        auto cor_index = inds[i].first;

        (begin + cor_index).get()->linkData(&(mbdd_data_vector[i]));
        (begin + cor_index).get()->updModelMatrix();
    }

    m_model_storage.fillBuffers();
}
template <typename DrawableType_, typename MBBDType, typename UBOType>
void
DrawableSystem<DrawableType_, MBBDType, UBOType>::update(
    SwapChainFrame& frame) const
{
    frame.updateMBDD(mbdd_data_vector);
    frame.updateUBO(m_ubo);
}

template <typename DrawableType_, typename MBBDType, typename UBOType>
void
DrawableSystem<DrawableType_, MBBDType, UBOType>::draw(
    const vk::CommandBuffer& command_buffer,
    const vk::PipelineLayout& pipelayout,
    SwapChainFrame& frame) const
{
}
}; // namespace render
}; // namespace kusengine

#endif // DRAWABLE_SYSTEM_HPP
