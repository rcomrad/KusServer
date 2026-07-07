#include "animation.hpp"

gpu::sprite::Animation::Animation(const TextureInfo& a_info) : m_uv(1.f, 1.f)
{
    m_uv /= a_info.dimensions;

    m_offsets    = calculateUVOffsets(m_uv, a_info.dimensions);
    m_frames_map = createFramesMap(a_info);
    m_name_map   = createNameMap(a_info);
}

void
gpu::sprite::Animation::drawAnimation(SpritePushData& a_push,
                                      type::AnimationFrame a_frame_num)
{
    a_push.uv_scaler       = {m_uv.x, m_uv.y};
    const auto& cur_offset = m_offsets[a_frame_num];
    a_push.uv_offset       = {cur_offset.x, cur_offset.y};
}

gpu::type::AnimationFrame
gpu::sprite::Animation::getAnimationFrame(int num, int time)
{
    return num;
}

std::vector<gpu::sprite::Animation::UV>
gpu::sprite::Animation::calculateUVOffsets(const core::Pair<float>& a_uv,
                                           type::Dimensions a_dimensions)
{
    std::vector<UV> result;
    for (int i = 0; i < a_dimensions.x; ++i)
    {
        for (int j = 0; j < a_dimensions.y; ++j)
        {
            result.emplace_back(a_uv * type::Dimensions(i, j));
        }
    }
    return result;
}

std::vector<std::vector<gpu::type::AnimationFrame>>
gpu::sprite::Animation::createFramesMap(const TextureInfo& a_info)
{
    std::vector<std::vector<type::AnimationFrame>> result;
    for (auto& [_, frames] : a_info.animation)
    {
        result.emplace_back();
        for (auto& num : frames)
        {
            result.back().emplace_back(num);
        }
    }
    return result;
}

std::unordered_map<std::string, int>
gpu::sprite::Animation::createNameMap(const TextureInfo& a_info)
{
    int num = 0;
    std::unordered_map<std::string, int> result;
    for (auto& [name, _] : a_info.animation)
    {
        result.emplace(name, num++);
    }
    return result;
}
