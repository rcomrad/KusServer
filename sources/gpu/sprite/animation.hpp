#pragma once

#include "kernel/utility/type/declaration/pair.hpp"
#include <vulkan/vulkan.hpp>

#include <string>
#include <unordered_map>
#include <vector>

#include "gpu/utils/typedef.hpp"

#include "sprite_push_data.hpp"
#include "texture_info.hpp"

namespace gpu::sprite
{
class Animation
{
    using UV = core::Pair<float>;

public:
    type::AnimationFrame getAnimationFrame(int a_anim_num, int time);

protected:
    Animation(const TextureInfo& a_info);

    void drawAnimation(SpritePushData& a_push,
                       type::AnimationFrame a_frame_num);

private:
    UV m_uv;

    std::vector<UV> m_offsets;
    std::vector<std::vector<type::AnimationFrame>> m_frames_map;
    std::unordered_map<std::string, int> m_name_map;

    static std::vector<UV> calculateUVOffsets(const core::Pair<float>& a_uv,
                                              type::Dimensions a_dimensions);
    static std::vector<std::vector<type::AnimationFrame>> createFramesMap(
        const TextureInfo& a_info);
    static std::unordered_map<std::string, int> createNameMap(
        const TextureInfo& a_info);
};

} // namespace gpu::sprite
