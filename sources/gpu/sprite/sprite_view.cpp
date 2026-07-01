#include "sprite_view.hpp"

gpu::sprite::SpriteView::SpriteView(Sprite& a_sprite,
                                    float a_offset_x,
                                    float a_offset_y)
    : m_offset_x(a_offset_x), m_offset_y(a_offset_y), m_sprite(a_sprite)
{
}

void
gpu::sprite::SpriteView::draw(vk::PipelineLayout a_pipeline_layout,
                              command::BaseCommand& a_cmd)
{
    SpritePushData push;
    m_sprite.draw(a_pipeline_layout, a_cmd, push);

    push.offset = {m_offset_x, m_offset_y};
    a_cmd.pushConstants(a_pipeline_layout,
                        vk::ShaderStageFlagBits::eVertex |
                            vk::ShaderStageFlagBits::eFragment,
                        0, sizeof(SpritePushData), &push);

    a_cmd.draw(6, 1, 0, 0);
}
