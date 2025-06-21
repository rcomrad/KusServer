#ifndef DRAWABLE_SYSTEM_HPP
#define DRAWABLE_SYSTEM_HPP

#include "engine/render_manager/model/model_storage.hpp"

#include "basic_drawable.hpp"

namespace kusengine
{
namespace render
{
class SwapChainFrame;

template <typename DrawableType, typename MBBDType>
class DrawableSystem
{
public:
    DrawableSystem() = default;

    template <typename Iterator>
    void resetDrawables(Iterator begin, Iterator end);

    void updateMBDD(SwapChainFrame& frame) const;

    void draw(const vk::CommandBuffer& command_buffer,
              const vk::PipelineLayout& pipelayout,
              SwapChainFrame& frame) const;

private:
    void generate();

    bool is_empty;

    ModelStorage<typename DrawableType::VertexType> m_model_storage;

    std::vector<MBBDType> mbdd_data_vector;
};

template <typename DrawableType, typename MBBDType>
template <typename Iterator>
void
DrawableSystem<DrawableType, MBBDType>::resetDrawables(Iterator begin,
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

}; // namespace render
}; // namespace kusengine

#endif // DRAWABLE_SYSTEM_HPP
