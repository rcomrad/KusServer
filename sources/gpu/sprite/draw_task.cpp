#include "draw_task.hpp"

#include "gpu/command/base_command.hpp"

#include "sprite.hpp"
#include "sprite_push_data.hpp"
#include "sprite_storage.hpp"

gpu::sprite::DrawTask::DrawTask(const SpriteView& a_sprite_view,
                                const type::NDC& a_offset,
                                int a_animation_id)
    : m_sprite_id(a_sprite_view.sprite_id),
      //   m_sprite(nullptr),
      m_offset(a_offset),
      m_animation_id(a_animation_id)
//   ,
//   m_animation_frame(0)
{
}

gpu::sprite::DrawTask::DrawTask(SpriteView a_sprite_view,
                                type::Coordinates a_offset,
                                int a_animation_id)
    : DrawTask(a_sprite_view, type::toNDC(a_offset), a_animation_id)
{
}

// void
// gpu::sprite::DrawTask::collapse(const SpriteStorage& a_storage)
// {
//     m_sprite          = *a_storage.getSpriteByID(m_sprite_id);
//     m_animation_frame = m_sprite->getAnimationFrame(a_animation_id, 0);
// }

void
gpu::sprite::DrawTask::execute(const SpriteStorage& a_storage,
                               vk::PipelineLayout a_pipeline_layout,
                               command::BaseCommand& a_cmd)
{
    const auto& sprite = a_storage.getSprite(m_sprite_id);

    SpritePushData push;
    // m_sprite->draw(a_pipeline_layout, a_cmd, push, m_animation_frame);
    sprite.draw(a_pipeline_layout, a_cmd, push, m_animation_id);

    push.coord_offset = {m_offset.x, m_offset.y};

    a_cmd.pushConstants(a_pipeline_layout,
                        vk::ShaderStageFlagBits::eVertex |
                            vk::ShaderStageFlagBits::eFragment,
                        0, sizeof(SpritePushData), &push);

    a_cmd.draw(6, 1, 0, 0);
}

// void
// gpu::sprite::DrawTask::selectAnimation(int a_anim_num)
// {
//     m_animation_frame = m_sprite.getAnimationFrame(a_anim_num, 0);
// }
