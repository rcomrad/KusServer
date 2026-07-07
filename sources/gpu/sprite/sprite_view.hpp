#pragma once

#include "gpu/command/base_command.hpp"
#include "gpu/pipeline/graphic_pipeline.hpp"
#include "gpu/utils/typedef.hpp"

#include "sprite.hpp"
#include "sprite_push_data.hpp"

namespace gpu::sprite
{

class SpriteView
{
public:
    SpriteView(Sprite& a_texture, type::NDC a_offset);

    void draw(vk::PipelineLayout a_pipeline_layout,
              command::BaseCommand& a_cmd);

    void selectAnimation(int a_anim_num);

private:
    type::NDC m_offset;
    sprite::Sprite& m_sprite;
    type::AnimationFrame m_animation_frame;
};

using SpriteViewArray = std::vector<sprite::SpriteView>;

} // namespace gpu::sprite
