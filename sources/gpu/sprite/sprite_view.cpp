#include "sprite_view.hpp"

gpu::sprite::SpriteView::SpriteView(Sprite& a_sprite, type::NDC a_offset)
    : m_offset(a_offset), m_sprite(a_sprite), m_animation_frame(0)
{
}

void
gpu::sprite::SpriteView::draw(vk::PipelineLayout a_pipeline_layout,
                              command::BaseCommand& a_cmd)
{
    SpritePushData push;
    m_sprite.draw(a_pipeline_layout, a_cmd, push, m_animation_frame);

    push.coord_offset = {m_offset.x, m_offset.y};

    a_cmd.pushConstants(a_pipeline_layout,
                        vk::ShaderStageFlagBits::eVertex |
                            vk::ShaderStageFlagBits::eFragment,
                        0, sizeof(SpritePushData), &push);

    a_cmd.draw(6, 1, 0, 0);
}

void
gpu::sprite::SpriteView::selectAnimation(int a_anim_num)
{
    m_animation_frame = m_sprite.getAnimationFrame(a_anim_num, 0);
}
